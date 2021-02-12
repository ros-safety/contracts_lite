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

#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/strictly_positive_real.hpp"
#include "gtest/gtest.h"

namespace c = contracts_lite;
static constexpr auto FEPS = 1e-4f;
static constexpr auto NaNf = std::numeric_limits<float>::quiet_NaN();
static constexpr auto INFf = std::numeric_limits<float>::infinity();

//------------------------------------------------------------------------------

TEST(Contract_Types, StrictlyPositiveReal_float) {
  constexpr auto VALID_VALUE = 0.5f * FEPS;
  EXPECT_THROW({ c::StrictlyPositiveReal<float>{NaNf}; }, std::runtime_error);
  EXPECT_THROW({ c::StrictlyPositiveReal<float>{INFf}; }, std::runtime_error);
  EXPECT_THROW({ c::StrictlyPositiveReal<float>{-NaNf}; }, std::runtime_error);
  EXPECT_THROW({ c::StrictlyPositiveReal<float>{-INFf}; }, std::runtime_error);
  EXPECT_THROW({ c::StrictlyPositiveReal<float>{-1.0f}; }, std::runtime_error);
  EXPECT_THROW({ c::StrictlyPositiveReal<float>{0.0f}; }, std::runtime_error);
  EXPECT_THROW(
      {
        c::StrictlyPositiveReal<float> r{VALID_VALUE};
        r = NaNf;
      },
      std::runtime_error);
  EXPECT_THROW(
      {
        c::StrictlyPositiveReal<float> r{VALID_VALUE};
        r = INFf;
      },
      std::runtime_error);
  EXPECT_THROW(
      {
        c::StrictlyPositiveReal<float> r{VALID_VALUE};
        r = r + INFf;
      },
      std::runtime_error);
  EXPECT_NO_THROW({
    c::StrictlyPositiveReal<float> r{VALID_VALUE};
    r = 1.0f;
    float tmp = r;
    r = tmp + 1.0f;
  });
}

//------------------------------------------------------------------------------
