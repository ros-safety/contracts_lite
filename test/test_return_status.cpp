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

#include "contracts_lite/contract_types.hpp"
#include "gtest/gtest.h"

TEST(Contracts_Lite, ReturnStatus) {
  EXPECT_TRUE(contracts_lite::ReturnStatus("test true", true));
  EXPECT_FALSE(contracts_lite::ReturnStatus("test false", false));
  EXPECT_TRUE(contracts_lite::ReturnStatus("", true));
  EXPECT_FALSE(contracts_lite::ReturnStatus("", false));

  {
    const auto rs1 = contracts_lite::ReturnStatus("status 1", true);
    const auto rs2 = contracts_lite::ReturnStatus("status 2", true);
    const auto rs = rs1 + rs2;
    EXPECT_TRUE(rs) << rs;
    EXPECT_EQ(rs.comment, "status 1; status 2") << rs;
  }

  {
    const auto rs1 = contracts_lite::ReturnStatus("status 1", true);
    const auto rs2 = contracts_lite::ReturnStatus("status 2", false);
    const auto rs = rs1 + rs2;
    EXPECT_FALSE(rs) << rs;
    EXPECT_EQ(rs.comment, "status 1; status 2") << rs;
  }

  {
    const auto rs1 = contracts_lite::ReturnStatus("status 1", false);
    const auto rs2 = contracts_lite::ReturnStatus("status 2", true);
    const auto rs = rs1 + rs2;
    EXPECT_FALSE(rs) << rs;
    EXPECT_EQ(rs.comment, "status 1; status 2") << rs;
  }

  {
    const auto rs1 = contracts_lite::ReturnStatus("status 1", false);
    const auto rs2 = contracts_lite::ReturnStatus("status 2", false);
    const auto rs = rs1 + rs2;
    EXPECT_FALSE(rs) << rs;
    EXPECT_EQ(rs.comment, "status 1; status 2") << rs;
  }
}
