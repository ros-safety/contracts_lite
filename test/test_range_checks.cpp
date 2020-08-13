// Copyright 2020 Mapless AI, Inc.
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

#include "contracts_lite/range_checks.hpp"
#include "gtest/gtest.h"

static constexpr auto NaN = std::numeric_limits<double>::quiet_NaN();
static constexpr auto Inf = std::numeric_limits<double>::infinity();
static constexpr auto MIN = -1.0;
static constexpr auto MAX = 1.0;

namespace r = contracts_lite::range_checks;

//------------------------------------------------------------------------------

TEST(Contracts_Lite, in_range_open_open) {
  {
    const auto status = r::in_range_open_open(0.0, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_open_open(0.5, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_open_open(-0.5, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_open_open(10.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_open_open(-10.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_open_open(1.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_open_open(-1.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_open_open(NaN, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_open_open(Inf, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
}

//------------------------------------------------------------------------------

TEST(Contracts_Lite, in_range_closed_open) {
  {
    const auto status = r::in_range_closed_open(0.0, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_closed_open(0.5, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_closed_open(-0.5, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_closed_open(10.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_closed_open(-10.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_closed_open(1.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_closed_open(-1.0, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_closed_open(NaN, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_closed_open(Inf, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
}

//------------------------------------------------------------------------------

TEST(Contracts_Lite, in_range_open_closed) {
  {
    const auto status = r::in_range_open_closed(0.0, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_open_closed(0.5, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_open_closed(-0.5, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_open_closed(10.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_open_closed(-10.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_open_closed(1.0, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_open_closed(-1.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_open_closed(NaN, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_open_closed(Inf, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
}

//------------------------------------------------------------------------------

TEST(Contracts_Lite, in_range_closed_closed) {
  {
    const auto status = r::in_range_closed_closed(0.0, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_closed_closed(0.5, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_closed_closed(-0.5, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_closed_closed(10.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_closed_closed(-10.0, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_closed_closed(1.0, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_closed_closed(-1.0, MIN, MAX);
    EXPECT_TRUE(status) << status;
  }
  {
    const auto status = r::in_range_closed_closed(NaN, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
  {
    const auto status = r::in_range_closed_closed(Inf, MIN, MAX);
    EXPECT_FALSE(status) << status;
  }
}

//------------------------------------------------------------------------------
