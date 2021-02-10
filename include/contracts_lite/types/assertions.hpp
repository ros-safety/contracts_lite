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

/// \copyright Copyright 2020 The Autoware Foundation
/// \file
/// \brief This file defines the autoware_auto_contracts real type.

#ifndef CONTRACTS__ASSERTIONS_HPP_
#define CONTRACTS__ASSERTIONS_HPP_

#include <string>
#include <utility>
#include <vector>

namespace contracts_lite {
namespace assertions {

/** @brief Enforce that a vector object is below capacity. */
template <typename T>
contracts_lite::ReturnStatus vector_below_capacity(const std::vector<T>& v) {
  const auto below_capacity = (v.size() < v.capacity());
  auto comment =
      CONTRACT_COMMENT("", "The vector's size (" + std::to_string(v.size()) +
                               ") must not exceed its capacity (" +
                               std::to_string(v.capacity()) + ")");
  return contracts_lite::ReturnStatus(std::move(comment), below_capacity);
}

}  // namespace assertions
}  // namespace contracts_lite

#endif  // CONTRACTS__ASSERTIONS_HPP_
