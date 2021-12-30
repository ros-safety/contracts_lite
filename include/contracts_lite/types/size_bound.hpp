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
/// \brief This file defines the size bound type.

#ifndef CONTRACTS__SIZE_BOUND_HPP_
#define CONTRACTS__SIZE_BOUND_HPP_

#include "contracts_lite/range_checks.hpp"

namespace contracts_lite {
/**
 * @brief Container for size bounds.
 *
 * @note A size bound is 'valid' if and only if it is in [0, BOUND]
 *
 * @invariant The value of these objects is guaranteed to be valid upon
 * successful construction.
 *
 * @implements{SRD006}
 */
template <size_t BOUND>
class SizeBound {
 public:
  SizeBound() = delete;

  /** @brief Allow objects to be directly cast to size types. */
  operator size_t() const { return r_; }

  /**
   * @brief Converting constructor for valid size bound objects.
   *
   * @post The class invariant validity condition holds (see invariant in
   * SizeBound).
   */
  SizeBound(size_t r) : r_(r) {
    DEFAULT_ENFORCE(contracts_lite::range_checks::in_range_closed_closed(
        r_, static_cast<size_t>(0), BOUND));
  }

 private:
  size_t r_;
};

}  // namespace contracts_lite

#endif  // CONTRACTS__SIZE_BOUND_HPP_
