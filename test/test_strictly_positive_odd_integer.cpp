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

#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/strictly_positive_odd_integer.hpp"

#include "gtest/gtest.h"

namespace c = contracts_lite;

//------------------------------------------------------------------------------

TEST(Contract_Types, StrictlyPositiveOddInteger) {
  EXPECT_THROW({ c::StrictlyPositiveOddInteger<int> s{0}; },
               std::runtime_error);
  EXPECT_THROW({ c::StrictlyPositiveOddInteger<int> s{2}; },
               std::runtime_error);
  EXPECT_THROW({ c::StrictlyPositiveOddInteger<unsigned int> s{2}; },
               std::runtime_error);
  EXPECT_THROW(
      {
        c::StrictlyPositiveOddInteger<size_t> s{1};
        s = 2;
      },
      std::runtime_error);
  EXPECT_THROW(
      {
        c::StrictlyPositiveOddInteger<unsigned int> s{1};
        s = 2;
      },
      std::runtime_error);
  EXPECT_THROW(
      {
        c::StrictlyPositiveOddInteger<int> s{1};
        s = 2;
      },
      std::runtime_error);
  EXPECT_NO_THROW({
    c::StrictlyPositiveOddInteger<int> s{1};
    s = 5;
  });
  EXPECT_NO_THROW({
    c::StrictlyPositiveOddInteger<size_t> s{1};
    s = 5;
  });

  typedef c::StrictlyPositiveOddInteger<int, 5> test_type;
  EXPECT_THROW({ test_type s{3}; }, std::runtime_error);
  EXPECT_NO_THROW({ test_type s{5}; });
  EXPECT_NO_THROW({ test_type s{7}; });

#if 0
  { c::StrictlyPositiveOddInteger<int, -1> this_should_not_compile{1}; }
#endif
#if 0
  {
    enum E : int {};
    c::StrictlyPositiveOddInteger<E> this_should_not_compile{static_cast<E>(1)};
  }
#endif
}

//------------------------------------------------------------------------------
