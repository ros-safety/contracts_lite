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

/**
 * @file enforcement.hpp
 * This file contains macros used for enforcement of contracts. Macros and
 * defines noted as "INTERNAL USE ONLY" are not part of the public API and
 * should not be used by client libraries.
 */

#ifndef CONTRACTS__ENFORCEMENT_HPP_
#define CONTRACTS__ENFORCEMENT_HPP_

#include <string>
#include <utility>

#include "contracts_lite/contract_violation.hpp"
#include "contracts_lite/failure_status.hpp"

/**
 * @brief Debug string definitions for continuation mode
 * @note INTERNAL USE ONLY
 */
#ifdef CONTRACT_VIOLATION_CONTINUATION_MODE_ON
#define CONTRACT_VIOLATION_CONTINUATION_MODE "ON"
#else
#define CONTRACT_VIOLATION_CONTINUATION_MODE "OFF"
#endif

/**
 * @brief Debug string definitions for build level
 * @note INTERNAL USE ONLY
 */
#ifdef CONTRACT_BUILD_LEVEL_OFF
#define CONTRACT_BUILD_LEVEL "OFF"
#elif defined(CONTRACT_BUILD_LEVEL_AUDIT)
#define CONTRACT_BUILD_LEVEL "AUDIT"
#else
#define CONTRACT_BUILD_LEVEL "DEFAULT"
#endif

/**
 * @brief Macro for constructing ContractViolation objects that inserts line
 * number, file name, and function name information.
 * @note Use std::source_location instead of __*__ macros when C++20 is
 * available.
 * @note INTERNAL USE ONLY
 */
#define CONTRACT_VIOLATION(comment)                      \
  ::autoware::contracts::ContractViolation(              \
      static_cast<uint_least32_t>(__LINE__), (comment),  \
      std::string(CONTRACT_BUILD_LEVEL),                 \
      std::string(CONTRACT_VIOLATION_CONTINUATION_MODE), \
      std::string(__FILE__), std::string(__func__))

/**
 * @brief Invokes violation handler if contract_check arg evaluates to `true`
 * @note INTERNAL USE ONLY
 */
#define ENFORCE_CONTRACT(contract_check)                    \
  if (auto is_failing = (contract_check)) {                 \
    CONTRACT_VIOLATION_HANDLER(                             \
        CONTRACT_VIOLATION(std::move(is_failing.comment))); \
  }

/**
 * @brief Invokes violation handler if assert_check arg is `true`
 * @note INTERNAL USE ONLY
 */
#define ENFORCE_ASSERTION(message, assert_check) \
  ENFORCE_CONTRACT(FailureStatus(message, assert_check))

/** @brief enforcement Macros that enforce contracts based on build level. */
#ifdef CONTRACT_BUILD_LEVEL_OFF
#define AUDIT_ENFORCE(contract_check)
#define DEFAULT_ENFORCE(contract_check)
#define AUDIT_CHECK(message, assert_check)
#define DEFAULT_CHECK(message, assert_check)
#elif defined(CONTRACT_BUILD_LEVEL_AUDIT)
#define AUDIT_ENFORCE(contract_check) ENFORCE_CONTRACT(contract_check)
#define DEFAULT_ENFORCE(contract_check) ENFORCE_CONTRACT(contract_check)
#define AUDIT_CHECK(message, assert_check) \
  ENFORCE_ASSERTION(message, assert_check)
#define DEFAULT_CHECK(message, assert_check) \
  ENFORCE_ASSERTION(message, assert_check)
#else
#define AUDIT_ENFORCE(contract_check)
#define DEFAULT_ENFORCE(contract_check) ENFORCE_CONTRACT(contract_check)
#define AUDIT_CHECK(message, assert_check)
#define DEFAULT_CHECK(message, assert_check) \
  ENFORCE_ASSERTION(message, assert_check)
#endif

#endif  // CONTRACTS__ENFORCEMENT_HPP_
