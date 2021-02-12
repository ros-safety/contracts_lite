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
/// \brief This file defines the acute radian type.

#ifndef CONTRACTS__ACUTE_RADIAN_HPP_
#define CONTRACTS__ACUTE_RADIAN_HPP_

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <utility>

#include "contracts_lite/range_checks.hpp"

namespace contracts_lite {
/** @brief Forward declaration for conversion functionality. */
template <typename T>
class AcuteDegree;

/**
 * @brief Container for acute radians.
 *
 * @note An acute radian is 'valid' if and only if it is in [0, pi/2).
 *
 * @invariant The float value of these objects is guaranteed to be valid upon
 * successful construction.
 *
 * @implements{SRD006}
 */
template <typename T>
class AcuteRadian {
  static_assert(std::numeric_limits<T>::is_iec559,
                "AcuteRadian numeric type must be IEEE float compliant.");

 public:
  AcuteRadian() = delete;

  /** @brief Allow objects to be directly cast to float types. */
  operator T() const;

  /**
   * @brief Conversion assignment from degrees.
   *
   * @post See AcuteRadian(T r)
   */
  AcuteRadian& operator=(AcuteDegree<T> d);

  /** @brief Make this explicit to distinguish from above. */
  AcuteRadian& operator=(T r);

  /**
   * @brief Conversion constructor from degrees.
   *
   * @post See AcuteRadian(T r)
   */
  AcuteRadian(AcuteDegree<T> r);

  /**
   * @brief Converting constructor for valid acute radian objects.
   *
   * @post The class invariant validity condition holds (see invariant in
   * AcuteRadian).
   */
  AcuteRadian(T r);

 private:
  T r_;

  /** @brief Conversion function. */
  static T degree_to_radian(T r);
};

}  // namespace contracts_lite

#include "contracts_lite/types/acute_degree.hpp"

namespace contracts_lite {

//------------------------------------------------------------------------------

template <typename T>
T AcuteRadian<T>::degree_to_radian(T r) {
  constexpr auto ratio = static_cast<T>(M_PI) / static_cast<T>(180);
  return r * ratio;
}

//------------------------------------------------------------------------------

template <typename T>
AcuteRadian<T>::operator T() const {
  return r_;
}

//------------------------------------------------------------------------------

template <typename T>
AcuteRadian<T>::AcuteRadian(AcuteDegree<T> r)
    : AcuteRadian<T>(AcuteRadian<T>::degree_to_radian(r)) {}

//------------------------------------------------------------------------------

template <typename T>
AcuteRadian<T>& AcuteRadian<T>::operator=(AcuteDegree<T> d) {
  *this = AcuteRadian<T>{AcuteRadian<T>::degree_to_radian(d)};
  return *this;
}

//------------------------------------------------------------------------------

template <typename T>
AcuteRadian<T>& AcuteRadian<T>::operator=(T r) {
  *this = AcuteRadian<T>{std::move(r)};
  return *this;
}

//------------------------------------------------------------------------------

template <typename T>
AcuteRadian<T>::AcuteRadian(T r) : r_(r) {
  DEFAULT_ENFORCE(contracts_lite::range_checks::in_range_closed_open(
      r_, static_cast<T>(0), static_cast<T>(M_PI * 0.5)));
}

//------------------------------------------------------------------------------

}  // namespace contracts_lite

#endif  // CONTRACTS__ACUTE_RADIAN_HPP_
