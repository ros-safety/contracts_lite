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

#ifndef CONTRACTS__RANGE_CHECKS_HPP_
#define CONTRACTS__RANGE_CHECKS_HPP_

#include <string>

#include "contracts_lite/contract_types.hpp"

namespace contracts_lite {
namespace range_checks {

/**
 * @brief Check whether value belongs to (min, max).
 *
 * @note To do the check, a value of type 'T' is cast to the bounds type 'U'.
 */
template <typename T, typename U>
ReturnStatus in_range_open_open(const T& value, const U& min, const U& max) {
  const auto inside_min = (static_cast<U>(value) > min);
  const auto inside_max = (static_cast<U>(value) < max);
  const auto comment = std::to_string(value) + " must be inside the range (" +
                       std::to_string(min) + ", " + std::to_string(max) + ")";
  return ReturnStatus(comment, inside_min && inside_max);
}

/**
 * @brief Check whether value belongs to [min, max).
 *
 * @note To do the check, a value of type 'T' is cast to the bounds type 'U'.
 */
template <typename T, typename U>
ReturnStatus in_range_closed_open(const T& value, const U& min, const U& max) {
  const auto inside_min = (static_cast<U>(value) >= min);
  const auto inside_max = (static_cast<U>(value) < max);
  const auto comment = std::to_string(value) + " must be inside the range [" +
                       std::to_string(min) + ", " + std::to_string(max) + ")";
  return ReturnStatus(comment, inside_min && inside_max);
}

/**
 * @brief Check whether value belongs to (min, max].
 *
 * @note To do the check, a value of type 'T' is cast to the bounds type 'U'.
 */
template <typename T, typename U>
ReturnStatus in_range_open_closed(const T& value, const U& min, const U& max) {
  const auto inside_min = (static_cast<U>(value) > min);
  const auto inside_max = (static_cast<U>(value) <= max);
  const auto comment = std::to_string(value) + " must be inside the range (" +
                       std::to_string(min) + ", " + std::to_string(max) + "]";
  return ReturnStatus(comment, inside_min && inside_max);
}

/**
 * @brief Check whether value belongs to [min, max].
 *
 * @note To do the check, a value of type 'T' is cast to the bounds type 'U'.
 */
template <typename T, typename U>
ReturnStatus in_range_closed_closed(const T& value, const U& min,
                                    const U& max) {
  const auto inside_min = (static_cast<U>(value) >= min);
  const auto inside_max = (static_cast<U>(value) <= max);
  const auto comment = std::to_string(value) + " must be inside the range [" +
                       std::to_string(min) + ", " + std::to_string(max) + "]";
  return ReturnStatus(comment, inside_min && inside_max);
}

}  // namespace range_checks
}  // namespace contracts_lite

#endif  // CONTRACTS__RANGE_CHECKS_HPP_
