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

#ifndef CONTRACTS__FAILURE_STATUS_HPP_
#define CONTRACTS__FAILURE_STATUS_HPP_

#include <string>
#include <utility>

namespace autoware {
namespace contracts {

/**
 * @brief Class defining boolean failure status with comment.
 *
 * A Status object contains a string message and boolean value. The message
 * describes the particular failure case being checked for, and the boolean
 * value indicates whether the failure has occured (true) or not (false).
 */
class FailureStatus {
 public:
  FailureStatus(std::string comment, bool is_failing)
      : comment(std::move(comment)), is_failing(is_failing) {}

  /**
   * @brief Conversion function to enable casting Status objects to bool values.
   * @return True iff the object indicates failure.
   */
  operator bool() const { return is_failing; }

  /**
   * @brief Human readable comment about nature of failure.
   * @note This only applies when the object casts to 'true'; else it should be
   * disregarded.
   */
  std::string comment;

 private:
  const bool is_failing;
};

}  // namespace contracts
}  // namespace autoware

#endif  // CONTRACTS__FAILURE_STATUS_HPP_
