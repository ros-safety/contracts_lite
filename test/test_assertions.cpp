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

#include <vector>

#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/assertions.hpp"
#include "gtest/gtest.h"

namespace c = contracts_lite;

//------------------------------------------------------------------------------

TEST(Contracts_Assertions, vector_below_capacity) {
  std::vector<int> v;
  v.reserve(2);

  // size 0, capacity 2
  EXPECT_NO_THROW(
      { DEFAULT_ENFORCE(c::assertions::vector_below_capacity(v)); });

  // size 1, capacity 2
  v.push_back(0);
  EXPECT_NO_THROW(
      { DEFAULT_ENFORCE(c::assertions::vector_below_capacity(v)); });

  // size 2, capacity 2
  v.push_back(0);
  EXPECT_THROW({DEFAULT_ENFORCE(c::assertions::vector_below_capacity(v))},
               std::runtime_error);
}

//------------------------------------------------------------------------------
