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
cmake_minimum_required(VERSION 3.10)

project(contracts_lite)

# For IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/types/acute_degree.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/types/acute_radian.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/types/nonnegative_real.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/types/nonzero_real.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/types/real.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/types/size_bound.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/types/strictly_positive_real.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/operators.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/enforcement.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/range_checks.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/contracts_lite/simple_violation_handler.hpp
)

# Build contracts library
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE "$<BUILD_INTERFACE:${HEADER_FILES}>")
target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)

# Uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
  )

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
  )
endif()

# Testing
if(BUILD_TESTING)
  enable_testing()
  find_package(GTest REQUIRED)
  include(GoogleTest)

  # Unit tests
  add_executable(test_${PROJECT_NAME}
    test/test_return_status.cpp
    test/test_range_checks.cpp
    test/test_to_string.cpp)
  target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME} GTest::GTest GTest::Main)
  gtest_discover_tests(test_${PROJECT_NAME})

  set(BUILD_DEFINITIONS
    -DCONTRACT_VIOLATION_CONTINUATION_MODE_ON
    -DCONTRACT_BUILD_LEVEL_AUDIT
  )

  add_executable(test_${PROJECT_NAME}_types
    test/test_acute_degree.cpp
    test/test_acute_radian.cpp
    test/test_dimensional_analysis.cpp
    test/test_nonnegative_real.cpp
    test/test_nonzero_real.cpp
    test/test_real.cpp
    test/test_size_bound.cpp
    test/test_strictly_positive_real.cpp)
  target_compile_definitions(test_${PROJECT_NAME}_types PRIVATE ${BUILD_DEFINITIONS})
  target_link_libraries(test_${PROJECT_NAME}_types ${PROJECT_NAME} GTest::GTest GTest::Main)
  gtest_discover_tests(test_${PROJECT_NAME}_types)
endif()

# Examples
if(BUILD_EXAMPLES)
  add_subdirectory(contracts_lite_example)
endif()

install(DIRECTORY include/contracts_lite
  DESTINATION include
)
