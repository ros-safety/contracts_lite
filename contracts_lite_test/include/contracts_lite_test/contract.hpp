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

#include "contracts_lite/contract_types.hpp"
#include "contracts_lite/to_string.hpp"

/**
 * @brief This include is the violation handler.
 *
 * This can be a user-provided file that defines a custom violation handler. A
 * simple default handler is provided as part of the contracts_lite library.
 */
#include "contracts_lite/simple_violation_handler.hpp"

namespace contracts_lite_test {
namespace example {

/**
 * This namespace contains the contract for the contracts::example library.
 */
namespace contract {
namespace preconditions {

/** @brief Check the preconditions of contracts_lite_test::example::foo */
template <typename T>
contracts_lite::ReturnStatus in_input_set(const T& bar) {
  static_assert(std::is_floating_point<const double>::value,
                "Input values to 'foo' must be floating point.");
  static const std::array<T, 6> S = {static_cast<T>(-5),  static_cast<T>(0),
                                     static_cast<T>(0.5), static_cast<T>(1),
                                     static_cast<T>(2.3), static_cast<T>(5)};

  const auto is_in_set = std::any_of(std::begin(S), std::end(S),
                                     [&bar](const T& s) { return s == bar; });

  return contracts_lite::ReturnStatus(
      "The value " + contracts_lite::gcc_7x_to_string_fix(bar) +
          " must be a member of the input set",
      is_in_set);
}

}  // namespace preconditions

namespace postconditions {

/** @brief Check all postconditions for function 'foo'. */
template <typename T>
contracts_lite::ReturnStatus foo(const T& bar) {
  static const std::array<T, 3> S = {static_cast<T>(0), static_cast<T>(1),
                                     static_cast<T>(5)};

  const auto is_in_set = std::any_of(std::begin(S), std::end(S),
                                     [&bar](const T& s) { return s == bar; });

  return contracts_lite::ReturnStatus(
      "The value " + contracts_lite::gcc_7x_to_string_fix(bar) +
          " must be a member of the output set",
      is_in_set);
}

}  // namespace postconditions

}  // namespace contract
}  // namespace example
}  // namespace contracts_lite_test

#endif  // EXAMPLE__CONTRACT__CONTRACT_HPP_
