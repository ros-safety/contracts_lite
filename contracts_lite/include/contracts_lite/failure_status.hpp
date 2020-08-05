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
  std::string comment;
  const bool is_failing;
};

}  // namespace contracts
}  // namespace autoware

#endif  // CONTRACTS__FAILURE_STATUS_HPP_
