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

#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/size_bound.hpp"

#include "gtest/gtest.h"

namespace c = contracts_lite;

//------------------------------------------------------------------------------

TEST(Contract_Types, SizeBound) {
  constexpr auto MAX = 10;
  EXPECT_THROW({ c::SizeBound<MAX>{11}; }, std::runtime_error);
  EXPECT_THROW(
      {
        c::SizeBound<MAX> s{0};
        s = 15;
      },
      std::runtime_error);
  EXPECT_NO_THROW({
    c::SizeBound<MAX> s{0};
    s = 5;
  });
}

//------------------------------------------------------------------------------
