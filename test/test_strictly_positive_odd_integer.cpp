/*
 * MIT License
 *
 * Copyright (c) 2021 Mapless AI, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "contracts_lite/simple_violation_handler.hpp"
#include "contracts_lite/types/strictly_positive_odd_integer.hpp"

#include "gtest/gtest.h"

namespace c = contracts_lite;

//------------------------------------------------------------------------------

TEST(Contract_Types, StrictlyPositiveOddInteger) {
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
  EXPECT_NO_THROW({
    c::StrictlyPositiveOddInteger<size_t> s{1};
    s = 5;
  });
}

//------------------------------------------------------------------------------
