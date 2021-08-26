/*
 * MIT License
 *
 * Copyright (c) 2021 Mapless AI, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

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
template <typename T>
class StrictlyPositiveOddInteger {
  static_assert(std::is_integral<T>::value,
                "StrictlyPositiveOddInteger types must be integral.");

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
      const auto is_odd = static_cast<bool>(r & static_cast<T>(1));
      auto comment = CONTRACT_COMMENT(
          "", gcc_7x_to_string_fix(r) + " must be strictly positive and odd.");
      return contracts_lite::ReturnStatus(std::move(comment),
                                          (is_strictly_positive && is_odd));
    }());
  }

 private:
  T r_;
};
}  // namespace contracts_lite

#endif  // CONTRACTS__STRICTLY_POSITIVE_ODD_INTEGER_HPP_
