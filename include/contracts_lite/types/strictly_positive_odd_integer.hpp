// Copyright 2021 Mapless AI, Inc.
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

/// \copyright Copyright 2021 Mapless AI, Inc.
/// \file
/// \brief This file defines the strictly positive odd integer type.

#ifndef CONTRACTS__STRICTLY_POSITIVE_ODD_INTEGER_HPP_
#define CONTRACTS__STRICTLY_POSITIVE_ODD_INTEGER_HPP_

#include <string>
#include <type_traits>
#include <utility>

#include "contracts_lite/operators.hpp"

namespace contracts_lite {
/**
 * @brief Container for strictly positive odd integers.
 *
 * @note A strictly positive odd integer is 'valid' if and only if it is in (0,
 * Inf) and it is congruent to 1(mod 2).
 *
 * @note Signed types are permitted to allow the check to fail on invalid input;
 * otherwise a negative value in a signed type might be cast to a postive value
 * in an unsigned type.
 *
 * @invariant The value of these objects is guaranteed to be valid upon
 * successful construction.
 *
 * @implements{SRD006}
 */
template <typename T, T Min = static_cast<T>(1)>
class StrictlyPositiveOddInteger {
  static_assert(std::is_integral<T>::value,
                "StrictlyPositiveOddInteger given non-integral type.");
  static_assert(
      Min > static_cast<T>(0),
      "StrictlyPositiveOddInteger given minimum value not greater than 0.");

 public:
  StrictlyPositiveOddInteger() = delete;

  /** @brief Allow objects to be directly cast to size types. */
  operator T() const { return r_; }

  /**
   * @brief Converting constructor for valid size bound objects.
   *
   * @post The class invariant validity condition holds (see invariant in
   * StrictlyPositiveOddInteger).
   */
  StrictlyPositiveOddInteger(T r) : r_(r) {
    DEFAULT_ENFORCE([&]() {
      const auto is_strictly_positive = (r > static_cast<T>(0));
      const auto is_not_less_than_min = (r >= Min);
      const auto is_odd = static_cast<bool>(r & static_cast<T>(1));
      auto comment = CONTRACT_COMMENT(
          "", gcc_7x_to_string_fix(r) +
                  " must be strictly positive, odd, and greater than " +
                  gcc_7x_to_string_fix(Min) + ".");
      return contracts_lite::ReturnStatus(
          std::move(comment),
          (is_strictly_positive && is_odd && is_not_less_than_min));
    }());
  }

 private:
  T r_;
};
}  // namespace contracts_lite

#endif  // CONTRACTS__STRICTLY_POSITIVE_ODD_INTEGER_HPP_
