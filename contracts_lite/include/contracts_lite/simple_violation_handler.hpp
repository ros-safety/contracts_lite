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

#ifndef CONTRACTS__SIMPLE_VIOLATION_HANDLER_HPP_
#define CONTRACTS__SIMPLE_VIOLATION_HANDLER_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>

#include "contracts_lite/contract_violation.hpp"

namespace autoware {
namespace contracts {

/**
 * @brief This function can be specified as the contract violation handler.
 * @note This function does not return. It throws std::runtime_error.
 */
inline void handler_with_continuation(const ContractViolation& violation) {
  throw std::runtime_error("CONTRACT VIOLATION!: " + violation.string());
}

/**
 * @brief This function can be specified as the contract violation handler.
 * @note This function does not return. It calls std::terminate.
 */
inline void handler_without_continuation(
    const ContractViolation& violation) noexcept {
  std::cerr << "CONTRACT VIOLATION!: " << violation << "\n";
  std::terminate();
}

}  // namespace contracts
}  // namespace autoware

/** @brief Define the build-dependent contract violation handler. */
#ifdef CONTRACT_VIOLATION_CONTINUATION_MODE_ON
#define CONTRACT_VIOLATION_HANDLER(violation) \
  ::autoware::contracts::handler_with_continuation(violation)
#else
#define CONTRACT_VIOLATION_HANDLER(violation) \
  ::autoware::contracts::handler_without_continuation(violation)
#endif

#include "contracts_lite/enforcement.hpp"

#endif  // CONTRACTS__SIMPLE_VIOLATION_HANDLER_HPP_
