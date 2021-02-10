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

/**
 * @file simple_violation_handler.hpp
 * @implements{SRD005}
 */

#ifndef CONTRACTS__SIMPLE_VIOLATION_HANDLER_HPP_
#define CONTRACTS__SIMPLE_VIOLATION_HANDLER_HPP_

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "contracts_lite/operators.hpp"

namespace contracts_lite {

/**
 * @brief This function can be specified as the contract violation handler.
 * @note This function does not return. It throws std::runtime_error.
 */
inline void handler_with_continuation(const ContractViolation& violation) {
  throw std::runtime_error("CONTRACT VIOLATION: " +
                           ContractViolation::string(violation));
}

/**
 * @brief This function can be specified as the contract violation handler.
 * @note This function does not return. It calls std::terminate.
 */
inline void handler_without_continuation(
    const ContractViolation& violation) noexcept {
  std::cerr << "CONTRACT VIOLATION: " << violation << "\n";
  std::terminate();
}

}  // namespace contracts_lite

/** @brief Define the build-dependent contract violation handler. */
#ifdef CONTRACT_VIOLATION_CONTINUATION_MODE_ON
#define CONTRACT_VIOLATION_HANDLER(violation) \
  ::contracts_lite::handler_with_continuation(violation)
#else
#define CONTRACT_VIOLATION_HANDLER(violation) \
  ::contracts_lite::handler_without_continuation(violation)
#endif

#include "contracts_lite/enforcement.hpp"

#endif  // CONTRACTS__SIMPLE_VIOLATION_HANDLER_HPP_
