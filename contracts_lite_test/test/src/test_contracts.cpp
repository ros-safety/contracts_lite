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

#include <limits>
#include <string>

#include "gtest/gtest.h"

#include "contracts/failure_status.hpp"
#include "contracts/to_string.hpp"

/**
 * @brief An object of type FailureStatus should always cast to the boolean
 * value of the 'is_failing' parameter.
 */
TEST(contracts, FailureStatus) {
  namespace ac = autoware::contracts;
  constexpr auto IS_FAILING = true;
  EXPECT_TRUE(ac::FailureStatus("", IS_FAILING));
  EXPECT_TRUE(ac::FailureStatus("test message", IS_FAILING));
  EXPECT_FALSE(ac::FailureStatus("", !IS_FAILING));
  EXPECT_FALSE(ac::FailureStatus("test message", !IS_FAILING));
}

/**
 * @brief gcc_7x_to_string_fix should be equivalent in functionality to
 * std::to_string. It is a workaround for this bug:
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=86274
 */
TEST(contracts, gcc_7x_to_string_fix) {
  namespace ac = autoware::contracts;
  constexpr auto NaN = std::numeric_limits<float>::quiet_NaN();
  constexpr auto Inf = std::numeric_limits<float>::infinity();

  EXPECT_EQ(ac::gcc_7x_to_string_fix(NaN), "nan");
  EXPECT_EQ(ac::gcc_7x_to_string_fix(Inf), "inf");
  EXPECT_EQ(ac::gcc_7x_to_string_fix(-1.0f), std::to_string(-1.0f));
  EXPECT_EQ(ac::gcc_7x_to_string_fix(0.0f), std::to_string(0.0f));
  EXPECT_EQ(ac::gcc_7x_to_string_fix(1.0f), std::to_string(1.0f));
}
