Contracts Types
===========

This package provides data types for use in contract enforcement and acts as a basic interface to the [Contracts Lite](README.md) library.

The provided data types can be used to perform per-parameter contract enforcement on input/output parameters.
In addition, the types can be used to perform basic dimensional analysis.

These types were originally defined in [merge request 695](https://gitlab.com/autowarefoundation/autoware.auto/AutowareAuto/-/merge_requests/695) for use in the [Autoware.Auto](https://www.autoware.auto/) project.

# Purpose / Use cases

Suppose there is a function that takes some floating point values as inputs and needs to do error checking on both input and output to ensure proper functioning:

```c++
/// \@brief Toy example of a function without contracts.
float foo(float height, float deg, float scalar, size_t count)
{
   if (!std::isfinite(height) || (height < 0.0f)) { throw ... }
   if (!((deg >= 0.0f) && (deg < 90.0f))) { throw ... }
   if (!std::isfinite(scalar)) { throw ... }
   if (count > SOME_BOUND) { throw ... }
   
   // Convert degrees to radians
   auto rad = some_conversion_function(deg);
   
   // do some work, compute 'bar' of type float
   
   if (!std::isfinite(bar) || (bar <= 0.0f)) { throw ... }
   return bar;
}
```

These types of checks can be very verbose, making the code difficult to read.
It can also be very error prone to maintain them over time.
The contract types provided by this library allow all of that error checking to be written _once_ and maintained in the _data type_:

```c++
#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/acute_degree.hpp"
#include "contracts_lite/types/nonnegative_real.hpp"
#include "contracts_lite/types/real.hpp"
#include "contracts_lite/types/size_bound.hpp"
#include "contracts_lite/types/strictly_positive_real.hpp"


/// \@brief Toy example of a function with contracts.
/// \@pre  0 <= height < inf
/// \@pre  0 <= deg < 90
/// \@pre  -inf < scalar < inf
/// \@pre  0 <= count <= SOME_BOUND
/// \@post 0 < ret < inf
StrictlyPositiveReal<float> foo(NonnegativeReal<float> height, AcuteDegree<float> deg, Real<float> scalar, SizeBound<SOME_BOUND> count)
{  
   // Convert degrees to radians
   AcuteRadian<float> rad = deg;
   
   // do some work, compute 'bar' of type float
   
   return bar;
}
```

Not only is the code less verbose, but it is much easier to maintain and the informative names make the code more readable.
Further, conversion between types can be built into the type itself.
For example, in the above code, conversion from degree to radian (or vice versa), is as simple as assigning one type to the other.

# Design

Because the [Contracts Lite](README.md) library uses compiler definitions to determine contract enforcement levels, the contracts library is implemented as a header-only library.
This prevents any mismatch in contract enforcement between a compiled contracts library and a compiled user library.

Each type is essentially a templated wrapper around another type.
For example, one of the types is `Real<T>`, which is intended to represent a finite floating point value.
To improve usability, the types allow implicit constructor conversion.
For example, the `foo` function defined above could be called as follows:

```c++
size_t count;
float height, deg, scalar;
auto bar = foo(height, deg, scalar, count);
```

Arguments will all be converted to the corresponding contract types and contracts will be enforced at run time.
A cast operator is also provided to aid template type deduction in certain cases:

```c++
auto bar = foo(height, deg, scalar, count);

float val = 1.0f;
auto max = std::max(val, static_cast<float>(bar));
```

The type definitions do not specify a violation handler, so a handler must explicitly included _before_ including any of the defined contract types.
The [Contracts Lite](README.md) library includes a `simple_violation_handler.hpp` for basic functionality.
See the unit tests for examples.

## Inputs / Outputs / API

To see all available contract types, check the `include` directory of the contracts package.

## Assumptions / Known limits

Users should be aware that contract enforcement, while generally cheap, is not free.
In performance sensitive applications it can make sense to move contract checks out of hot spots.
For example, the below code constructs a contract type at every iteration:

```c++
#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/real.hpp"

Real<float> foo(Real<float> base, Real<float> step) {
  for (auto i=0; i<99999999; ++i) {
    base = base + step;
  }
  return base;
}
```

Unless it's required to enforce the contract at each iteration, a logically equivalent, but more performant version of the code would be:

```c++
#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/real.hpp"

Real<float> foo(Real<float> base, Real<float> step) {
  float b = base;
  float s = step;
  for (auto i=0; i<99999999; ++i) {
    b = b + s;
  }
  return b;
}
```

Also be aware that using the `AUDIT` build level (see [Error detection and handling](#error-detection-and-handling)) can significantly impact performance.
This is because verbose comment message are generated each time a contract is checked.

## Error detection and handling

Contract violations are handled by the user specified violation handler.
The behavior of the handler is determined by the compile defines described in the [Contracts Lite](README.md) library.
