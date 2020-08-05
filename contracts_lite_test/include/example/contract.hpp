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

#ifndef EXAMPLE__CONTRACT__CONTRACT_HPP_
#define EXAMPLE__CONTRACT__CONTRACT_HPP_

#include <algorithm>
#include <array>
#include <type_traits>

#include "contracts_lite/failure_status.hpp"
#include "contracts_lite/to_string.hpp"

/**
 * @brief This include is the violation handler.
 *
 * This can be a user-provided file that defines a custom violation handler. A
 * simple default handler is provided as part of the library.
 */
#include "contracts_lite/simple_violation_handler.hpp"

namespace autoware {
namespace contracts {
namespace example {

/** @brief This namespace contains the contract for the contracts::example
 * library. */
namespace contract {

/** @brief These checks must be true upon entering the body of
 * contracts::example::foo. */
namespace preconditions {

/** @brief Check that input to 'foo' is valid. */
template <typename T>
FailureStatus in_input_set(const T& bar) {
  static_assert(std::is_floating_point<const double>::value,
                "Input values to 'foo' must be floating point.");
  static const std::array<T, 6> S = {static_cast<T>(-5),  static_cast<T>(0),
                                     static_cast<T>(0.5), static_cast<T>(1),
                                     static_cast<T>(2.3), static_cast<T>(5)};

  const auto is_not_in_set = std::all_of(
      std::begin(S), std::end(S), [&bar](const T& s) { return s != bar; });

  return FailureStatus("The value " + gcc_7x_to_string_fix(bar) +
                           " is not a member of the input set",
                       is_not_in_set);
}

}  // namespace preconditions

/** @brief These checks must be true upon exit of the body of
 * contracts::example::foo. */
namespace postconditions {

/**
 * @brief Check all postconditions for function 'foo'.
 * @pre The value satisfies all of contract::foo::assertions.
 */
template <typename T>
FailureStatus foo(const T& bar) {
  static const std::array<T, 3> S = {static_cast<T>(0), static_cast<T>(1),
                                     static_cast<T>(5)};

  const auto is_not_in_set = std::all_of(
      std::begin(S), std::end(S), [&bar](const T& s) { return s != bar; });

  return FailureStatus("The value " + gcc_7x_to_string_fix(bar) +
                           " is not a member of the output set",
                       is_not_in_set);
}

}  // namespace postconditions

}  // namespace contract
}  // namespace example
}  // namespace contracts
}  // namespace autoware

#endif  // EXAMPLE__CONTRACT__CONTRACT_HPP_
