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

#define _USE_MATH_DEFINES
#include <cmath>

#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/acute_degree.hpp"
#include "contracts_lite/types/acute_radian.hpp"
#include "gtest/gtest.h"

namespace c = contracts_lite;
static constexpr auto FEPS = 1e-4f;
static constexpr auto quarter_turn_rad = static_cast<float>(M_PI) / 4.0f;

//------------------------------------------------------------------------------

TEST(Contracts_DimensionalAnalysis, AcuteDegree_float) {
  const c::AcuteDegree<float> d{45.0f};
  EXPECT_NEAR(c::AcuteRadian<float>{d}, quarter_turn_rad, FEPS);

  const c::AcuteRadian<float> r = d;
  EXPECT_NEAR(r, quarter_turn_rad, FEPS);
}

//------------------------------------------------------------------------------

TEST(Contracts_DimensionalAnalysis, AcuteRadian_float) {
  const c::AcuteRadian<float> r{quarter_turn_rad};
  ASSERT_EQ(r, quarter_turn_rad);
  EXPECT_NEAR(c::AcuteDegree<float>{r}, 45.0f, FEPS);

  const c::AcuteDegree<float> d = r;
  EXPECT_NEAR(d, 45.0f, FEPS);
}

//------------------------------------------------------------------------------
