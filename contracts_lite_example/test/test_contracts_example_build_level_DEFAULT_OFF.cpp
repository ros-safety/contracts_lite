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

#include <cstdlib>

#include "contracts_lite_example/simple.hpp"

//-----------------------------------------------------------------------------

/**
 * @brief With build level DEFAULT, contract enforcement is disabled for AUDIT
 * level. Expect no errors for any AUDIT level contracts.
 */
TEST(contracts, example_with_build_level_DEFAULT_OFF) {
  namespace ex = contracts_lite_test::example;

  const auto no_violation = 5.0f;
  EXPECT_EXIT(
      {
        ex::foo(no_violation);
        exit(EXIT_SUCCESS);
      },
      ::testing::ExitedWithCode(EXIT_SUCCESS), "");

  const auto violate_precondition = 10.0f;
  EXPECT_DEATH(ex::foo(violate_precondition), "");

  const auto violate_assertion_0 = 2.3f;
  EXPECT_DEATH(ex::foo(violate_assertion_0), "");

  const auto violate_assertion_1 = -5.0f;
  EXPECT_DEATH(ex::foo(violate_assertion_1), "");

  const auto violate_assertion_2 = 0.0f;
  EXPECT_EXIT(
      {
        ex::foo(violate_assertion_2);
        exit(EXIT_SUCCESS);
      },
      ::testing::ExitedWithCode(EXIT_SUCCESS), "");

  const auto violate_postcondition = 0.5f;
  EXPECT_DEATH(ex::foo(violate_postcondition), "");
}

//-----------------------------------------------------------------------------
