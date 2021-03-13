// Copyright 2021 Mapless AI, Inc.
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

/// \copyright Copyright 2021 Mapless AI, Inc.
/// \file
/// \brief This file defines the non-negative real type.

#include <limits>

#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/nonzero_real.hpp"
#include "gtest/gtest.h"

namespace c = contracts_lite;
static constexpr auto NaNf = std::numeric_limits<float>::quiet_NaN();
static constexpr auto INFf = std::numeric_limits<float>::infinity();

//------------------------------------------------------------------------------

TEST(Contract_Types, NonzeroReal_float) {
  EXPECT_THROW({ c::NonzeroReal<float>{NaNf}; }, std::runtime_error);
  EXPECT_THROW({ c::NonzeroReal<float>{INFf}; }, std::runtime_error);
  EXPECT_THROW({ c::NonzeroReal<float>{-NaNf}; }, std::runtime_error);
  EXPECT_THROW({ c::NonzeroReal<float>{-INFf}; }, std::runtime_error);
  EXPECT_THROW({ c::NonzeroReal<float> r{0.0f}; }, std::runtime_error);
  EXPECT_THROW({ c::NonzeroReal<float> r{-0.0f}; }, std::runtime_error);
  EXPECT_THROW(
      {
        c::NonzeroReal<float> r{0.0f};
        r = NaNf;
      },
      std::runtime_error);
  EXPECT_THROW(
      {
        c::NonzeroReal<float> r{0.0f};
        r = INFf;
      },
      std::runtime_error);
  EXPECT_THROW(
      {
        c::NonzeroReal<float> r{0.0f};
        r = r + INFf;
      },
      std::runtime_error);
  EXPECT_NO_THROW({
    c::NonzeroReal<float>{1.0f};
    c::NonzeroReal<float>{-1.0f};
    {
      c::NonzeroReal<float> r{1.0f};
      r = -1.0f;
      float tmp = r;
      r = tmp + 2.0f;
    }
  });
}

//------------------------------------------------------------------------------
