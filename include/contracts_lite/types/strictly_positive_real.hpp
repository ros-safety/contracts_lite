// Copyright 2020 The Autoware Foundation
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

/// \copyright Copyright 2020 The Autoware Foundation
/// \file
/// \brief This file defines the strictly positive real type.

#ifndef CONTRACTS__STRICTLY_POSITIVE_REAL_HPP_
#define CONTRACTS__STRICTLY_POSITIVE_REAL_HPP_

#include <limits>

#include "contracts_lite/range_checks.hpp"

namespace contracts_lite {
/**
 * @brief Container for strictly positive reals.
 *
 * @note A strictly positive real is 'valid' if and only if it is in (0, inf)
 *
 * @invariant The float value of these objects is guaranteed to be valid upon
 * successful construction.
 *
 * @implements{SRD007}
 */
template <typename T>
class StrictlyPositiveReal {
  static_assert(
      std::numeric_limits<T>::is_iec559,
      "StrictlyPositiveReal numeric type must be IEEE float compliant.");

 public:
  StrictlyPositiveReal() = delete;

  /** @brief Allow objects to be directly cast to float types. */
  operator T() const { return r_; }

  /**
   * @brief Converting constructor for valid strictly positive real objects.
   *
   * @post The class invariant validity condition holds (see invariant in
   * StrictlyPositiveReal).
   */
  StrictlyPositiveReal(T r) : r_(r) {
    DEFAULT_ENFORCE(contracts_lite::range_checks::in_range_open_open(
        r_, static_cast<T>(0), std::numeric_limits<T>::infinity()));
  }

 private:
  T r_;
};

}  // namespace contracts_lite

#endif  // CONTRACTS__STRICTLY_POSITIVE_REAL_HPP_
