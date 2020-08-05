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

#include "gtest/gtest.h"

#include "contracts_lite_test/simple.hpp"

//-----------------------------------------------------------------------------

/** @brief With build level AUDIT, all contract enforcement is enabled. */
TEST(contracts, example_with_build_level_AUDIT) {
  namespace ex = contracts_lite_test::example;

  const auto no_violation = 5.0f;
  EXPECT_NO_THROW({ ex::foo(no_violation); });

  const auto violate_precondition = 10.0f;
  EXPECT_THROW({ ex::foo(violate_precondition); }, std::runtime_error);

  const auto violate_assertion_0 = 2.3f;
  EXPECT_THROW({ ex::foo(violate_assertion_0); }, std::runtime_error);

  const auto violate_assertion_1 = -5.0f;
  EXPECT_THROW({ ex::foo(violate_assertion_1); }, std::runtime_error);

  const auto violate_assertion_2 = 0.0f;
  EXPECT_THROW({ ex::foo(violate_assertion_2); }, std::runtime_error);

  const auto violate_postcondition = 0.5f;
  EXPECT_THROW({ ex::foo(violate_postcondition); }, std::runtime_error);
}

//-----------------------------------------------------------------------------
