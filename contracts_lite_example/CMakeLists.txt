# Copyright 2020 Mapless AI, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Function for creating gtest targets at different build levels
function(build_level_targets BUILD_LEVEL)
  set(TARGET_SUFFIX _build_level_${BUILD_LEVEL})
  set(BUILD_DEFINITIONS
    -DCONTRACT_VIOLATION_CONTINUATION_MODE_ON
    -DCONTRACT_BUILD_LEVEL_${BUILD_LEVEL}
  )

  enable_testing()
  find_package(GTest REQUIRED)
  include(GoogleTest)

  # Define example libraries
  add_library(example${TARGET_SUFFIX} INTERFACE)
  target_include_directories(example${TARGET_SUFFIX} INTERFACE include)
  target_link_libraries(example${TARGET_SUFFIX} INTERFACE contracts_lite)

  # Unit tests
  set(TEST_EXE test_${PROJECT_NAME}_example${TARGET_SUFFIX})
  add_executable(${TEST_EXE} test/test_contracts_example${TARGET_SUFFIX}.cpp)
  target_compile_definitions(${TEST_EXE} PRIVATE ${BUILD_DEFINITIONS})
  target_link_libraries(${TEST_EXE} example${TARGET_SUFFIX} GTest::GTest GTest::Main)
  gtest_discover_tests(${TEST_EXE})
endfunction()

# Test all three build level targets
build_level_targets("DEFAULT")
build_level_targets("OFF")
build_level_targets("AUDIT")
