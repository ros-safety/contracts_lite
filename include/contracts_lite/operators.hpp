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

#ifndef CONTRACTS__CONTRACT_TYPES_HPP_
#define CONTRACTS__CONTRACT_TYPES_HPP_

#include <cmath>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

/**
 * @brief Macro for choosing comment verbosity based on enforcement level.
 *
 * @note This is useful when the contract check is intended for default
 * enforcement, but you'd like to generate a much more informative (i.e.,
 * expensive) comment during audit enforcement.
 */
#ifdef CONTRACT_BUILD_LEVEL_OFF
#define CONTRACT_COMMENT(default_comment, audit_comment) ""
#elif defined(CONTRACT_BUILD_LEVEL_AUDIT)
#define CONTRACT_COMMENT(default_comment, audit_comment) (audit_comment)
#else
#define CONTRACT_COMMENT(default_comment, audit_comment) (default_comment)
#endif

/**
 * @brief This namespace contains data strutures, functions, and macros used to
 * enforce run-time contracts.
 * @note For reference, see:
 * http://open-std.org/JTC1/SC22/WG21/docs/papers/2018/p0542r5.html
 */
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

/**
 * @brief Class defining boolean return status with comment.
 *
 * A Status object contains a string message and boolean value. The message
 * describes how to interpret the boolean return value.
 */
struct ReturnStatus {
  ReturnStatus(std::string comment, bool status)
      : comment(std::move(comment)), status(status) {}
  ReturnStatus(ReturnStatus& rs)
      : ReturnStatus(std::move(rs.comment), rs.status) {}
  ReturnStatus(ReturnStatus&& rs)
      : ReturnStatus(std::move(rs.comment), rs.status) {}

  /** @brief Disallow default construction. */
  ReturnStatus() = delete;

  /** @brief Allow objects to be directly cast to bool types. */
  operator bool() const { return status; }

  /** @brief Print status object to stream. */
  friend std::ostream& operator<<(std::ostream& os, const ReturnStatus& r) {
    return (os << r.comment);
  }

  std::string comment;  // TODO(jeff): use std::string_view in C++17
  const bool status;

  friend ReturnStatus operator&&(const ReturnStatus& rs1,
                                 const ReturnStatus& rs2);

  friend ReturnStatus operator||(const ReturnStatus& rs1,
                                 const ReturnStatus& rs2);

 private:
  static std::string join_comments(const std::string& conjunction,
                                   const std::string& comment1,
                                   const std::string comment2) {
    if (comment1.empty()) {
      return comment2;
    } else if (comment2.empty()) {
      return comment1;
    }
    return (comment1 + conjunction + comment2);
  }
};

/**
 * @brief Concatenate status objects (useful for chaining assertions).
 * @note This is defined as a non-member function because, as a member function,
 * overload resolution will first cast the objects to bool, then to int, and
 * attempt to use the integer addition operator.
 */
inline ReturnStatus operator&&(const ReturnStatus& rs1,
                               const ReturnStatus& rs2) {
  const auto conjunction = "; AND ";
  auto comment =
      ReturnStatus::join_comments(conjunction, rs1.comment, rs2.comment);
  return ReturnStatus(std::move(comment), (rs1.status && rs2.status));
}
inline ReturnStatus operator||(const ReturnStatus& rs1,
                               const ReturnStatus& rs2) {
  const auto conjunction = "; OR ";
  auto comment =
      ReturnStatus::join_comments(conjunction, rs1.comment, rs2.comment);
  return ReturnStatus(std::move(comment), (rs1.status || rs2.status));
}

/** @brief Data structure for information describing contract violations. */
struct ContractViolation {
  const uint_least32_t line_number;
  const std::string comment;
  const std::string assertion_level;
  const std::string violation_continuation_mode;
  const std::string file_name;
  const std::string function_name;

  /** @brief Stream overload for printing contract violation to string. */
  friend std::ostream& operator<<(std::ostream& os,
                                  const ContractViolation cv) {
    os << "{comment: \"" << cv.comment << "\", function_name: \""
       << cv.function_name << "\", file_name: \"" << cv.file_name
       << "\", line_number: \"" << cv.line_number << "\", assertion_level: \""
       << cv.assertion_level << "\", violation_continuation_mode: \""
       << cv.violation_continuation_mode << "\"}";
    return os;
  }

  /** @brief Convenience method to get string version of this object. */
  static std::string string(const ContractViolation& cv) {
    std::stringstream ss;
    ss << cv;
    return ss.str();
  }

  ContractViolation(uint_least32_t line_number, std::string comment,
                    std::string assertion_level,
                    std::string violation_continuation_mode,
                    std::string file_name, std::string function_name)
      : line_number(line_number),
        comment(std::move(comment)),
        assertion_level(std::move(assertion_level)),
        violation_continuation_mode(std::move(violation_continuation_mode)),
        file_name(std::move(file_name)),
        function_name(std::move(function_name)) {}
};

}  // namespace contracts_lite

#endif  // CONTRACTS__CONTRACT_TYPES_HPP_
