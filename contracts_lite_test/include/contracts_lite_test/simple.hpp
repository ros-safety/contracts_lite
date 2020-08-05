// Copyright 2020 Mapless AI, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef EXAMPLE__SIMPLE_HPP_
#define EXAMPLE__SIMPLE_HPP_

#include <cmath>
#include <limits>

#include "contracts_lite_test/contract.hpp"

namespace contracts_lite_test {

/**
 * @brief This namespace contains a simple example library along with a contract
 * to demonstrate usage.
 */
namespace example {

/**
 * @brief This function is an example of using a contract library to enforce a
 * function contract.
 *
 * The contract for this function is just an arbitrary restriction on values
 * that the input variable can take on at various places in the function flow.
 * The contract itself is purely for demonstration purposes; it is not of
 * practical interest.
 *
 * @pre The input value to 'foo' must be in the set {-5.0, 0.0, 1.0, 2.3, 5.0}.
 * The values in the set are arbitrary and chosen only to demonstrate how such a
 * requirement can be enforced. The size of the set is chosen such that it is
 * large enough for valid input values to demonstrate violation other contract
 * checks. For example, in a contract with three checks, the valid set of inputs
 * would need to be at least size four to exercise all check paths (3 fails + 1
 * pass).
 *
 * @post The output value must be in the set {1.0, 5.0}. Because this is part of
 * a demonstration library, the size of the set must be at least two in order to
 * demonstrate one passing condition and one failing condition. The values in
 * the set are chosen to correspond to values in the precondition set that are
 * not already used to demonstrate failure conditions of other contract checks.
 */
template <typename T>
T foo(T bar) {
  DEFAULT_ENFORCE(contract::preconditions::in_input_set(bar));

  // Intentionally violate an assertion
  if (bar == static_cast<T>(1)) {
    bar = std::numeric_limits<float>::quiet_NaN();
  }
  DEFAULT_ENFORCE([&]() {
    return contracts_lite::ReturnStatus("'bar' must not be NaN here",
                                        !std::isnan(bar));
  }());

  // Check for assertion violation
  AUDIT_ENFORCE([&]() {
    return contracts_lite::ReturnStatus("'bar' must not be zero here",
                                        (bar != static_cast<T>(0)));
  }());

  // Intentionally violate a postcondition
  if (bar == static_cast<T>(-5)) {
    bar = std::numeric_limits<float>::quiet_NaN();
  }
  DEFAULT_ENFORCE(contract::postconditions::foo(bar));

  return bar;
}

}  // namespace example

}  // namespace contracts_lite_test

#endif  // EXAMPLE__SIMPLE_HPP_
