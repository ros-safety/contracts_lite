Contracts
===========

This is the design document for the `contracts` package.

# Purpose / Use cases

The purpose of this package is to provide a standard practice and tooling to support the explicit definition and enforcement of function contracts.

# Usage

## Prerequisites

- CMake >= 3.10
- GTest (if building tests)
- A C++14-capable compiler

## Instructions

Clone the repository and `cd` into the cloned folder and then:

```console
mkdir build && cd build
cmake ..
make install
```

**Note:** The last command may require super-user privileges i.e. `sudo`.

If you wish to build the tests or the example, you can add the `-DBUILD_TESTING` or `-DBUILD_EXAMPLES` flags, respectively:

```console
mkdir build && cd build
cmake .. -DBUILD_TESTING=on -DBUILD_EXAMPLES=on
make
make install
```

The easiest way to run all of the tests on Linux is with a script similar to the following:

```console
for exec in $(find . -executable -type f -name 'test*'); do $exec; done
```

For convenience, this script is provided as `run_tests.sh` in the repo root.

# Design

This package is designed to mimic the behavior and specification of contracts as described in the [C++20 proposal](http://open-std.org/JTC1/SC22/WG21/docs/papers/2018/p0542r5.html).
The proposal defines a "contract" as a collection of preconditions, postconditions, and assertions defined for a given function. These are defined as:

- **precondition**: A condition that must be true upon entering the function body.
This is typically a test that requires some property to hold for the function input.
- **postcondition**: A condition that must be true upon function body exit.
This is typically a test that requires some property to hold for the function return value.
- **assertions**: These are conditions that must be true at one or more points in the function body interior.
These are typically tests that require some property to hold for intermediate function values.

The contract library provides macros that invoke a *violation handler* when contract checks fail.
The default violation handler prints an error to `std::cerr` and calls `std::terminate`.
An additional handler is provided that throws a `std::runtime_error` exception with the violation error message.
The choice of which handler to use is made at build time by selecting the contraction *continuation mode*:

- **continuation mode off**: Execution does not continue beyond contract violation; upon being invoked, the violation handler terminates the process.
- **continuation mode on**: Execution is allowed to continue beyond contraction violation; the handler throws an exception and it is up to the process to handle the error.

> Note: Continuation mode 'on' is only intended for testing and debugging purposes, for example, writing unit tests to verify contract enforcement, or to verify contract-enforced library behavior.
In normal usage, continuation mode should typically be 'off'.

Finally, it may be the case that verifying contract conditions is undesirable or impractical to do under normal operating conditions, but is desirable under testing conditions.
This can happen when testing the contract is computationally expensive compared to the evaluation of the function itself.
So we would like to distinguish between contracts that should always be enforced and those that should only be enforced during a system audit.
To distinguish these cases, there are two build levels that define contract enforcement:

- **build level default**: Contracts enforced at the default level are always checked when contracts are enabled.
- **build level audit**: Contracts enforced at the audit level are only checked when contracts are enabled and the build level is set to `audit`.

## Inputs / Outputs / API

Using the contracts library requires that the build configuration be set and that a contract enforcement library be implemented. This section covers both of those.

### Build configuration

For most use cases, the default build configuration will be sufficient and users will not need to do anything here. However, when implementing unit tests, it may sometimes be useful to change the build configuration.

By design, the continuation mode and build level are specified at build time. During compilation, the code looks for the following defines to decide how to build the library (see enforcement.hpp):

- `CONTRACT_VIOLATION_CONTINUATION_MODE_(ON|OFF)`: If no define is given for continuation mode, `OFF` is assumed
- `CONTRACT_BUILD_LEVEL_(OFF|DEFAULT|AUDIT)`: If no define is given for build level, `DEFAULT` is assumed.
(If `OFF` is set, all contract enforcement is compiled out.)

### Contract enforcement library

The minimum required to use the contracts library is to implement contract checks as functions that return an object of type `contracts_lite::ReturnStatus`.
The ReturnStatus object contains a message describing the particular failure case being checked for and a boolean value indicating whether the failure has occurred (true) or not (false).

Once the contract checks have been implemented, they can be invoked in library functions using the enforcement macros.
Two enforcement macros are provided to allow enforcement at the 'default' and 'audit' levels:

- `DEFAULT_ENFORCE(ReturnStatus)`: invokes violation handler if ReturnStatus arg is `false`
- `AUDIT_ENFORCE(ReturnStatus)`: invokes violation handler if ReturnStatus arg is `false`

When writing functions that check contract conditions, use the comment field of the ReturnStatus object to describe the specific conditions of failure (e.g. what value resulted in a failed check). The next section gives an example of this.

### Working example

For a working example of contract enforcement, see [`contracts_lite_test`](contracts_lite_test).
That package contains minimal example library, its contract, and unit tests showing its enforcement under various build levels.

### Pseudo-code example

Consider a library:

```
namespace my_lib
{

  /**
   * @brief Some description of what 'my_func' does.
   *
   * @pre Input must be less than -1 or greater than +1
   * @post Input must be greater than -0.5 and less than 0.5
   */
  int my_func(int arg);

}  // namespace
```

The contract library for `my_func` would be defined as:

```
namespace my_lib
{
namespace contract
{

namespace preconditions
{
  ReturnStatus input_is_good(int arg);
}  // namespace preconditions

namespace postconditions
{
  ReturnStatus output_is_good(int arg);
}  // namespace postconditions

}  // namespace contract
}  // namespace my_lib
```

In the definition of `my_lib`, the contract is enforced using macros provided by this library:

```
namespace my_lib
{

  int my_func(int arg)
  {
    DEFAULT_ENFORCE(contract::preconditions::input_is_good(arg));

    // ... code ...

    DEFAULT_ENFORCE([&] () {
      return ReturnStatus("arg must be greater than zero", (arg > 0));
    }());

    // ... code ...

    DEFAULT_ENFORCE(contract::postconditions::output_is_good(arg));
    return arg;
  }

}  // namespace my_lib
```

## User-defined violation handler

The user is free to define arbitrary custom violation handlers. To do so, the `CONTRACT_VIOLATION_HANDLER` macro must be defined to take an argument of type contracts_lite::ReturnStatus, and the enforcement.hpp must be included after that macro is defined. A bare minimum example would be something like:

```
#define CONTRACT_VIOLATION_HANDLER(violation) std::terminate()

#include "contracts/enforcement.hpp"
```

To properly handle different continuation modes, a handler might look something like:

```
#ifdef CONTRACT_VIOLATION_CONTINUATION_MODE_ON
#define CONTRACT_VIOLATION_HANDLER(violation) throw std::runtime_error("CONTRACT VIOLATION!: " + violation.string());
#else
#define CONTRACT_VIOLATION_HANDLER(violation) {std::cerr << violation; std::terminate();}
#endif

#include "contracts/enforcement.hpp"
```

For reference, see simple_violation_handler.hpp.

## Error detection and handling
<!-- Required -->

The contracts library is strictly an enforcement mechanism.
It does not itself perform any error detection.
Error handling is always either calling `std::terminate` or throwing `std::runtime_error`.

# References / External links

- [A Contract Design](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0380r1.pdf)
- [Support for contract based programming in C++](http://open-std.org/JTC1/SC22/WG21/docs/papers/2018/p0542r5.html)

# Future extensions / Unimplemented parts

Ultimately this library should be replaced with C++20 contracts when they become part of the language.
That will not necessarily be a trivial operation, but by following the conventions of the C++20 proposal, it should at least be a largely mechanical operation.

# Related issues

- https://gitlab.com/autowarefoundation/autoware.auto/AutowareAuto/-/issues/520
