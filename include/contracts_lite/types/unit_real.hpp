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
/// \brief This file defines the unit real type.

#ifndef CONTRACTS__UNIT_REAL_H_
#define CONTRACTS__UNIT_REAL_H_

#include <limits>

#include <contracts_lite/range_checks.hpp>
#include <contracts_lite/simple_violation_handler.hpp>

namespace contracts_lite {
/**
 * @brief Container for unit reals.
 *
 * @note A unit real is 'valid' iff it is in [0, 1].
 *
 * @invariant The float value of these objects is guaranteed to be valid upon
 * successful construction.
 *
 * @implements{SRD006}
 */
template <typename T>
class UnitReal {
  static_assert(std::numeric_limits<T>::is_iec559,
                "Unit real numeric type must be IEEE float compliant.");

 public:
  UnitReal() = delete;

  /** @brief Allow objects to be directly cast to float types. */
  operator T() const { return r_; }

  /**
   * @brief Converting constructor for valid unit real objects.
   *
   * @post The the class invariant validity condition holds (see invariant in
   * UnitReal).
   */
  UnitReal(T r) : r_(r) {
    auto in_range = contracts_lite::range_checks::in_range_closed_closed(
        r_, static_cast<T>(0), static_cast<T>(1));
    DEFAULT_ENFORCE(std::move(in_range));
  }

 private:
  T r_;
};

}  // namespace contracts_lite

#endif  // CONTRACTS__UNIT_REAL_H_
