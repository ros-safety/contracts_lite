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
/// \brief This file defines the real type.

#ifndef CONTRACTS__REAL_HPP_
#define CONTRACTS__REAL_HPP_

#include <limits>

#include "contracts_lite/range_checks.hpp"

namespace contracts_lite {
/**
 * @brief Container for reals.
 *
 * @note A real is 'valid' if and only if it is in (-inf, inf).
 *
 * @invariant The float value of these objects is guaranteed to be valid upon
 * successful construction.
 */
template <typename T>
class Real {
  static_assert(std::numeric_limits<T>::is_iec559,
                "Real numeric type must be IEEE float compliant.");

 public:
  Real() = delete;

  /** @brief Allow objects to be directly cast to float types. */
  operator T() const { return r_; }

  /**
   * @brief Converting constructor for valid real objects.
   *
   * @post The class invariant validity condition holds (see invariant in Real).
   */
  Real(T r) : r_(r) {
    DEFAULT_ENFORCE(contracts_lite::range_checks::in_range_open_open(
        r_, -std::numeric_limits<T>::infinity(),
        std::numeric_limits<T>::infinity()));
  }

 private:
  T r_;
};

}  // namespace contracts_lite

#endif  // CONTRACTS__REAL_HPP_
