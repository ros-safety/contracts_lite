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
cmake_minimum_required(VERSION 3.5)

project(contracts_lite_test)

# For IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# dependencies
find_package(ament_cmake_auto REQUIRED)

# Testing
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(contracts_lite REQUIRED)
  ament_lint_auto_find_test_dependencies()

  # Function for creating gtest targets at different build levels
  function(build_level_targets BUILD_LEVEL)
    set(TARGET_SUFFIX _build_level_${BUILD_LEVEL})
    set(BUILD_DEFINITIONS
      -DCONTRACT_VIOLATION_CONTINUATION_MODE_ON
      -DCONTRACT_BUILD_LEVEL_${BUILD_LEVEL}
    )

    # Define example libraries
    add_library(example${TARGET_SUFFIX} INTERFACE)
    target_include_directories(example${TARGET_SUFFIX} INTERFACE include)

    # Unit tests
    set(TEST_EXE test_${PROJECT_NAME}_example${TARGET_SUFFIX})
    ament_add_gtest(${TEST_EXE} test/src/gtest_main.cpp test/src/test_contracts_example${TARGET_SUFFIX}.cpp)
    target_compile_definitions(${TEST_EXE} PRIVATE ${BUILD_DEFINITIONS})
    ament_target_dependencies(${TEST_EXE} contracts_lite)
    target_link_libraries(${TEST_EXE} example${TARGET_SUFFIX})
  endfunction()

  # Test all three build level targets
  build_level_targets("DEFAULT")
  build_level_targets("OFF")
  build_level_targets("AUDIT")

endif()

# ament package generation and installing
ament_auto_package()
