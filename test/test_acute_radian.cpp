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
#define _USE_MATH_DEFINES
#include <cmath>

#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/acute_radian.hpp"
#include "gtest/gtest.h"

namespace c = contracts_lite;
static constexpr auto NaNf = std::numeric_limits<float>::quiet_NaN();
static constexpr auto INFf = std::numeric_limits<float>::infinity();

//------------------------------------------------------------------------------

TEST(Contract_Types, AcuteRadian_float) {
  EXPECT_THROW({ c::AcuteRadian<float>{NaNf}; }, std::runtime_error);
  EXPECT_THROW({ c::AcuteRadian<float>{INFf}; }, std::runtime_error);
  EXPECT_THROW({ c::AcuteRadian<float>{-NaNf}; }, std::runtime_error);
  EXPECT_THROW({ c::AcuteRadian<float>{-INFf}; }, std::runtime_error);
  EXPECT_THROW(
      {
        c::AcuteRadian<float> r = 1.0f;
        r = 2.0f;
      },
      std::runtime_error);
  EXPECT_NO_THROW({
    c::AcuteRadian<float> r = 1.0f;
    r = 0.75f;
  });
}

//------------------------------------------------------------------------------
