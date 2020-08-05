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

#ifndef CONTRACTS__TO_STRING_HPP_
#define CONTRACTS__TO_STRING_HPP_

#include <cmath>
#include <string>

namespace contracts_lite {

/**
 * @brief Workaround for bug in std::to_string in gcc 7.x
 * @note See: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=86274
 */
template <typename T>
std::string gcc_7x_to_string_fix(const T& val) {
  if (std::isnan(val)) {
    return "nan";
  }
  if (std::isinf(val)) {
    return "inf";
  }
  return std::to_string(val);
}

}  // namespace contracts_lite

#endif  // CONTRACTS__TO_STRING_HPP_
