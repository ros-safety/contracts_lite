/*
 * Copyright 2020 Mapless AI, Inc.
 *
 * Proprietary License
 */
#include <gtest/gtest.h>

#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/scalar_flicker.hpp"

namespace c = contracts_lite;

//------------------------------------------------------------------------------

TEST(Contracts_ScalarFlicker, PeakIndex_indices_are_valid) {
  EXPECT_THROW({ (c::PeakIndex<float, 3>{0, 0, 1}); }, std::runtime_error);
  EXPECT_THROW({ (c::PeakIndex<float, 3>{3, 5, 5}); }, std::runtime_error);
  EXPECT_THROW({ (c::PeakIndex<float, 3>{3, 2, 1}); }, std::runtime_error);
  EXPECT_THROW({ (c::PeakIndex<float, 3>{2, 2, 2}); }, std::runtime_error);
  EXPECT_NO_THROW({
    (c::PeakIndex<float, 3>{0, 1, 2});
    (c::PeakIndex<float, 3>{0, 1, 20});
    (c::PeakIndex<float, 3>{3, 5, 17});
  });
}

//------------------------------------------------------------------------------

TEST(Contracts_ScalarFlicker, PeakIndex_is_valid_for_array) {
  const std::array<float, 3> arr = {0.0f, 1.0f, 0.0f};

  {
    const auto peak = c::PeakIndex<float, 3>(0, 1, 2);
    EXPECT_TRUE((c::PeakIndex<float, 3>::is_valid_for_array(arr, peak)));
  }

  {
    const auto peak = c::PeakIndex<float, 3>(0, 1, 5);
    EXPECT_FALSE((c::PeakIndex<float, 3>::is_valid_for_array(arr, peak)));
  }
}

//------------------------------------------------------------------------------

TEST(Contracts_ScalarFlicker, is_peak) {
  EXPECT_TRUE(c::is_peak(0, 1, 0));
  EXPECT_TRUE(c::is_peak(0, 3, 2));
  EXPECT_TRUE(c::is_peak(1, 3, -1));
  EXPECT_FALSE(c::is_peak(0, 0, 0));
  EXPECT_FALSE(c::is_peak(0, -1, 0));
  EXPECT_FALSE(c::is_peak(1, -1, 0));
  EXPECT_FALSE(c::is_peak(0, -1, 1));
}

//------------------------------------------------------------------------------

TEST(Contracts_ScalarFlicker, is_valley) {
  EXPECT_FALSE(c::is_valley(0, 1, 0));
  EXPECT_FALSE(c::is_valley(0, 3, 2));
  EXPECT_FALSE(c::is_valley(1, 3, -1));
  EXPECT_FALSE(c::is_valley(0, 0, 0));
  EXPECT_TRUE(c::is_valley(0, -1, 0));
  EXPECT_TRUE(c::is_valley(1, -1, 0));
  EXPECT_TRUE(c::is_valley(0, -1, 1));
}

//------------------------------------------------------------------------------

TEST(Contracts_ScalarFlicker, peak_mag) {
  {
    const auto expected_mag = 2.0f;
    const auto mag = c::peak_mag(1.0f, 3.0f, 0.0f);
    EXPECT_EQ(mag, expected_mag);
  }

  {
    const auto expected_mag = 2.0f;
    const auto mag = c::peak_mag(0.0f, 3.0f, 1.0f);
    EXPECT_EQ(mag, expected_mag);
  }

  {
    const auto expected_mag = 2.0f;
    const auto mag = c::peak_mag(-3.0f, 3.0f, 1.0f);
    EXPECT_EQ(mag, expected_mag);
  }

  {
    const auto expected_mag = 6.0f;
    const auto mag = c::peak_mag(-3.0f, 3.0f, -5.0f);
    EXPECT_EQ(mag, expected_mag);
  }
}

//------------------------------------------------------------------------------

TEST(Contracts_ScalarFlicker, valley_mag) {
  {
    const auto expected_mag = 6.0f;
    const auto mag = c::valley_mag(3.0f, -3.0f, 5.0f);
    EXPECT_EQ(mag, expected_mag);
  }

  {
    const auto expected_mag = 3.0f;
    const auto mag = c::valley_mag(0.0f, -3.0f, 5.0f);
    EXPECT_EQ(mag, expected_mag);
  }

  {
    const auto expected_mag = 3.0f;
    const auto mag = c::valley_mag(5.0f, -3.0f, 0.0f);
    EXPECT_EQ(mag, expected_mag);
  }

  {
    const auto expected_mag = 3.0f;
    const auto mag = c::valley_mag(0.0f, -3.0f, 0.0f);
    EXPECT_EQ(mag, expected_mag);
  }
}

//------------------------------------------------------------------------------

TEST(Contracts_ScalarFlicker, rotate_left_and_set_back) {
  std::array<float, 4> arr = {0.0f, 1.0f, 2.0f, 3.0f};
  const std::array<float, 4> arr_expected = {1.0f, 2.0f, 3.0f, 4.0f};
  c::rotate_left_and_set_back(arr, 4.0f);
  for (auto i = 0; i < 4; ++i) {
    EXPECT_EQ(arr[i], arr_expected[i]);
  }
}

//------------------------------------------------------------------------------

TEST(Contracts_ScalarFlicker, greatest_magnitude_peak) {
  const std::array<float, 9> arr = {-1.5f, 1.0f, -2.0f, -3.0f, -1.0f,
                                    -5.0f, 0.0f, 1.0f,  2.0f};

  {
    const auto peak = c::greatest_magnitude_peak(arr);
    const auto mag = c::get_peak_magnitude(arr, peak);
    EXPECT_EQ(mag, 6.0f) << "peak: " << peak;
  }

  {
    constexpr auto begin = 0;
    constexpr auto end = arr.size();
    const auto peak = c::greatest_magnitude_peak(arr, begin, end);
    const auto mag = c::get_peak_magnitude(arr, peak);
    EXPECT_EQ(mag, 3.5f);
  }

  {
    constexpr auto begin = 0;
    constexpr auto end = 3;
    const auto peak = c::greatest_magnitude_peak(arr, begin, end);
    const auto mag = c::get_peak_magnitude(arr, peak);
    EXPECT_EQ(mag, 2.5f);
  }

  {
    constexpr auto begin = 6;
    constexpr auto end = arr.size();
    const auto peak = c::greatest_magnitude_peak(arr, begin, end);
    const auto mag = c::get_peak_magnitude(arr, peak);
    EXPECT_EQ(mag, 0.0f);
  }
}

//------------------------------------------------------------------------------

TEST(Contracts_ScalarFlicker, ScalarFlicker) {
  constexpr auto FLICKER_LIMIT = 0.5f;
  auto sf = c::ScalarFlicker<float, 3>(FLICKER_LIMIT);

  EXPECT_TRUE(sf.no_flicker(0.0f));
  EXPECT_TRUE(sf.no_flicker(1.0f));
  EXPECT_TRUE(sf.no_flicker(2.0f));
  EXPECT_FALSE(sf.no_flicker(1.0f));
  EXPECT_TRUE(sf.no_flicker(0.0f));
  EXPECT_TRUE(sf.no_flicker(-1.0f));
  EXPECT_FALSE(sf.no_flicker(0.0f));
}

//------------------------------------------------------------------------------
