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

#ifndef CONTRACTS__CONTRACT_VIOLATION_HPP_
#define CONTRACTS__CONTRACT_VIOLATION_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>

namespace autoware {
/**
 * @brief This namespace contains data strutures, functions, and macros used to
 * enforce run-time contracts.
 * @note For reference, see:
 * http://open-std.org/JTC1/SC22/WG21/docs/papers/2018/p0542r5.html
 */
namespace contracts {

/** @brief Data structure for violation handling. */
struct ContractViolation {
  const uint_least32_t line_number;
  const std::string comment;
  const std::string assertion_level;
  const std::string violation_continuation_mode;
  const std::string file_name;
  const std::string function_name;

  /** @brief Convience stream overload for printing contract violation to
   * string. */
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
  std::string string() const {
    std::stringstream ss;
    ss << *this;
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

}  // namespace contracts
}  // namespace autoware

#endif  // CONTRACTS__CONTRACT_VIOLATION_HPP_
