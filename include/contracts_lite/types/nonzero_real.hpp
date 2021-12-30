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
/// \brief This file defines the non-zero real type.

#ifndef CONTRACTS__NONZERO_REAL_H_
#define CONTRACTS__NONZERO_REAL_H_

#include <limits>

#include <contracts_lite/range_checks.hpp>
#include <contracts_lite/simple_violation_handler.hpp>

namespace contracts_lite {
/**
 * @brief Container for non-zero reals.
 *
 * @note A non-zero real is 'valid' iff it is in (-inf, 0) \cup (0, inf).
 *
 * @invariant The float value of these objects is guaranteed to be valid upon
 * successful construction.
 *
 * @implements{SRD006}
 */
template <typename T>
class NonzeroReal {
  static_assert(std::numeric_limits<T>::is_iec559,
                "Non-zero real numeric type must be IEEE float compliant.");

 public:
  NonzeroReal() = delete;

  /** @brief Allow objects to be directly cast to float types. */
  operator T() const { return r_; }

  /**
   * @brief Converting constructor for valid non-zero real objects.
   *
   * @post The the class invariant validity condition holds (see invariant in
   * NonzeroReal).
   */
  NonzeroReal(T r) : r_(r) {
    const auto in_lower_range =
        contracts_lite::range_checks::in_range_open_open(
            r_, -std::numeric_limits<T>::infinity(), static_cast<T>(0));
    const auto in_upper_range =
        contracts_lite::range_checks::in_range_open_open(
            r_, static_cast<T>(0), std::numeric_limits<T>::infinity());
    DEFAULT_ENFORCE(in_lower_range || in_upper_range);
  }

 private:
  T r_;
};

}  // namespace contracts_lite

#endif  // CONTRACTS__NONZERO_REAL_H_
