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
/// \brief This file defines the flicker test.

#ifndef CONTRACTS__SCALAR_FLICKER_HPP_
#define CONTRACTS__SCALAR_FLICKER_HPP_

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>

using contracts_lite::gcc_7x_to_string_fix;

namespace contracts_lite {
/**
 * @brief convenience container for peak indices.
 * @note The class is templated with respect to the array type it indexes into.
 */
template <typename T, size_t S>
class PeakIndex {
 public:
  size_t p1_idx;
  size_t p2_idx;
  size_t p3_idx;

  static std::string string(const PeakIndex& peak);

  /** @brief Stream overload for convenience. */
  friend std::ostream& operator<<(std::ostream& os, const PeakIndex& peak) {
    return os << PeakIndex::string(peak);
  }

  /** @brief Only use factory method for building objects. */
  PeakIndex() = delete;

  /** @brief Build and return a peak index object. */
  PeakIndex(size_t p1_idx, size_t p2_idx, size_t p3_idx);

  /**
   * @brief Test whether peak indices are valid w.r.t. a given array.
   * @note This method only validates the indices, not the values they point to.
   * @return true iff all peak indices exist within arr.
   */
  static bool is_valid_for_array(const std::array<T, S>& arr,
                                 const PeakIndex& peak);

 private:
  /**
   * @brief Test that peak indices are semantically valid.
   * @return true iff p1_idx < p2_idx < p3_idx.
   */
  static bool indices_are_valid(size_t p1_idx, size_t p2_idx, size_t p3_idx);
};  // class PeakIndex

//------------------------------------------------------------------------------

template <typename T, size_t S>
PeakIndex<T, S>::PeakIndex(size_t p1_idx, size_t p2_idx, size_t p3_idx)
    : p1_idx(p1_idx), p2_idx(p2_idx), p3_idx(p3_idx) {
  DEFAULT_ENFORCE([&]() {
    auto comment =
        CONTRACT_COMMENT("", "Input indices must be ordered with p1_idx (" +
                                 std::to_string(p1_idx) + ") < p2_idx (" +
                                 std::to_string(p2_idx) + ") < p3_idx (" +
                                 std::to_string(p3_idx) + ")");
    return contracts_lite::ReturnStatus(
        std::move(comment),
        PeakIndex<T, S>::indices_are_valid(p1_idx, p2_idx, p3_idx));
  }());
}

//------------------------------------------------------------------------------

template <typename T, size_t S>
std::string PeakIndex<T, S>::string(const PeakIndex<T, S>& peak) {
  return "[" + std::to_string(peak.p1_idx) + ", " +
         std::to_string(peak.p2_idx) + ", " + std::to_string(peak.p3_idx) + "]";
}

//------------------------------------------------------------------------------

template <typename T, size_t S>
bool PeakIndex<T, S>::indices_are_valid(size_t p1_idx, size_t p2_idx,
                                        size_t p3_idx) {
  const auto p1_before_p2 = (p1_idx < p2_idx);
  const auto p2_before_p3 = (p2_idx < p3_idx);
  return p1_before_p2 && p2_before_p3;
}

//------------------------------------------------------------------------------

template <typename T, size_t S>
bool PeakIndex<T, S>::is_valid_for_array(const std::array<T, S>& arr,
                                         const PeakIndex<T, S>& peak) {
  const auto p1_idx_valid = (peak.p1_idx < arr.size());
  const auto p2_idx_valid = (peak.p2_idx < arr.size());
  const auto p3_idx_valid = (peak.p3_idx < arr.size());
  return p1_idx_valid && p2_idx_valid && p3_idx_valid;
}

//------------------------------------------------------------------------------

/**
 * @brief Test whether three values form a peak.
 * @pre values are real-valued and finite.
 * @pre p1, p2, and p3 are sequential and in that order.
 * @return true iff (p1 < p2) and (p3 < p2)
 */
template <typename T>
bool is_peak(const T& p1, const T& p2, const T& p3) {
  const auto p1_below_p2 = (p1 < p2);
  const auto p3_below_p2 = (p3 < p2);
  return p1_below_p2 && p3_below_p2;
}

/**
 * @brief Test whether three values form a peak.
 * @pre values are real-valued and finite.
 * @pre p1, p2, and p3 are sequential and in that order.
 * @return true iff (p1 > p2) and (p3 > p2)
 */
template <typename T>
bool is_valley(const T& p1, const T& p2, const T& p3) {
  const auto p1_above_p2 = (p1 > p2);
  const auto p3_above_p2 = (p3 > p2);
  return p1_above_p2 && p3_above_p2;
}

/**
 * @brief Distance from peak to the nearest of its predecessor or successor.
 * @note Behavior is undefined if values do not form a peak.
 * @return Unsigned distance.
 */
template <typename T>
T peak_mag(const T& p1, const T& p2, const T& p3) {
  return p2 - std::max(p1, p3);
}

/**
 * @brief Distance from peak value to the nearest of its predeccor or successor.
 * @note Behavior is undefined if values do not form a valley.
 * @return Unsigned distance.
 */
template <typename T>
T valley_mag(const T& p1, const T& p2, const T& p3) {
  return std::min(p1, p3) - p2;
}

/**
 * @brief Compute the magnitude of a given peak.
 * @pre The indices of peak are valid w.r.t. arr.
 * @return Magnitude of the peak, or 0 if the indices do not form a peak.
 */
template <typename T, size_t S>
T get_peak_magnitude(const std::array<T, S>& arr, const PeakIndex<T, S>& peak) {
  static_assert(S > 2,
                "An array requires at least three elements to have a peak.");
  const auto& p1 = arr[peak.p1_idx];
  const auto& p2 = arr[peak.p2_idx];
  const auto& p3 = arr[peak.p3_idx];

  const auto is_p = is_peak(p1, p2, p3);
  const auto p_mag = peak_mag(p1, p2, p3);
  const auto is_v = is_valley(p1, p2, p3);
  const auto v_mag = valley_mag(p1, p2, p3);

  // Only branch when returning.
  if (is_p) {
    return p_mag;
  } else if (is_v) {
    return v_mag;
  }
  return static_cast<T>(0);
}

/**
 * @brief arr: [0, 1, 2, 3] and val: 4 becomes [1, 2, 3, 4]
 */
template <typename T, size_t S>
void rotate_left_and_set_back(std::array<T, S>& arr, T val) {
  static_assert(S > 0, "Can't set an element of an empty array.");
  std::rotate(arr.begin(), std::next(arr.begin()), arr.end());
  arr.back() = std::move(val);
}

/**
 * @brief Compute the greatest peak magnitude between two indices in an array.
 * @pre begin and end are valid peak indices into arr.
 * @return The abs. magnitude of the largest peak, or zero if there is no peak.
 */
template <typename T, size_t S>
PeakIndex<T, S> greatest_magnitude_peak(const std::array<T, S>& arr,
                                        size_t begin, size_t end) {
  static_assert(S > 2,
                "An array requires at least three elements to have a peak.");
  const auto p1_idx = begin;
  const auto p2_idx_initial = (p1_idx + 1);
  const auto p3_idx = (end - 1);

  auto max_mag = static_cast<T>(0);
  auto max_peak = PeakIndex<T, S>(p1_idx, p2_idx_initial, p3_idx);
  for (auto p2_idx = p2_idx_initial; p2_idx < p3_idx; ++p2_idx) {
    const auto peak = PeakIndex<T, S>(p1_idx, p2_idx, p3_idx);
    const auto mag = get_peak_magnitude(arr, peak);
    if (mag > max_mag) {
      max_mag = mag;
      max_peak = peak;
    }
  }
  return max_peak;
}

/**
 * @brief Compute the greatest peak magnitude between two indices in an array.
 * @pre begin and end are valid indices into arr with end > begin.
 */
template <typename T, size_t S>
PeakIndex<T, S> greatest_magnitude_peak(const std::array<T, S>& arr) {
  static_assert(S > 2,
                "An array requires at least three elements to have a peak.");
  const auto p1_idx_initial = 0u;
  auto p2_idx_initial = (p1_idx_initial + 1u);
  auto p3_idx_initial = (p2_idx_initial + 1u);
  auto max_mag = static_cast<T>(0);
  auto max_peak =
      PeakIndex<T, S>(p1_idx_initial, p2_idx_initial, p3_idx_initial);
  for (auto p1_idx = p1_idx_initial; p1_idx < (arr.size() - 2u); ++p1_idx) {
    p2_idx_initial = (p1_idx + 1u);
    p3_idx_initial = (p2_idx_initial + 1u);
    for (auto p3_idx = p3_idx_initial; p3_idx < arr.size(); ++p3_idx) {
      const auto begin = p1_idx;
      const auto end = (p3_idx + 1u);
      const auto peak = greatest_magnitude_peak(arr, begin, end);
      const auto mag = get_peak_magnitude(arr, peak);
      if (mag > max_mag) {
        max_mag = mag;
        max_peak = peak;
      }
    }
  }
  return max_peak;
}

/**
 * @brief Utility class to encapsulate data structure and flicker computation.
 */
template <typename T, size_t S>
class ScalarFlicker {
  static_assert(S > 2, "Cannot test for flicker with window size < 3.");

 public:
  explicit ScalarFlicker(T limit);
  ScalarFlicker(T limit, std::string name);
  static ScalarFlicker build(T limit);
  T new_peak_magnitude(T val);
  contracts_lite::ReturnStatus no_flicker(T val);

 private:
  T limit_;
  std::string name_;
  std::array<T, S> window_;
};  // class ScalarFlicker

//------------------------------------------------------------------------------

template <typename T, size_t S>
ScalarFlicker<T, S>::ScalarFlicker(T limit, std::string name)
    : limit_(std::move(limit)), name_("[" + name + "]: ") {
  DEFAULT_ENFORCE([&]() {
    return contracts_lite::ReturnStatus(name_ + "Magnitude limit (" +
                                            gcc_7x_to_string_fix(limit) +
                                            ") must be strictly positive.",
                                        (limit > static_cast<T>(0)));
  }());

  window_.fill(static_cast<T>(0));
}

//------------------------------------------------------------------------------

template <typename T, size_t S>
ScalarFlicker<T, S>::ScalarFlicker(T limit)
    : ScalarFlicker(std::move(limit), "Flicker") {}

//------------------------------------------------------------------------------

template <typename T, size_t S>
contracts_lite::ReturnStatus ScalarFlicker<T, S>::no_flicker(T val) {
  rotate_left_and_set_back(window_, std::move(val));
  const auto peak = greatest_magnitude_peak(window_);
  const auto mag = get_peak_magnitude(window_, peak);
  const auto no_flicker = (mag < limit_);
  auto comment = CONTRACT_COMMENT(
      "", (name_ + "Magnitude (" + gcc_7x_to_string_fix(mag) + ") of peak at " +
           PeakIndex<T, S>::string(peak) + " must be less than the limit (" +
           gcc_7x_to_string_fix(limit_) + ")"));
  return contracts_lite::ReturnStatus(std::move(comment), no_flicker);
}

//------------------------------------------------------------------------------

}  // namespace contracts_lite

#endif  // CONTRACTS__SCALAR_FLICKER_HPP_
