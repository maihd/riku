# CMake project autogenerated by GENie
cmake_minimum_required(VERSION 2.8.4)

project(riku.unit_tests)
set(
source_list
  ../../../../unit_tests/test_array.cc
  ../../../../unit_tests/test_crypto.cc
  ../../../../unit_tests/test_date.cc
  ../../../../unit_tests/test_dictionary.cc
  ../../../../unit_tests/test_events.cc
  ../../../../unit_tests/test_fiber.cc
  ../../../../unit_tests/test_fs.cc
  ../../../../unit_tests/test_func.cc
  ../../../../unit_tests/test_hash_table.cc
  ../../../../unit_tests/test_json.cc
  ../../../../unit_tests/test_list.cc
  ../../../../unit_tests/test_math.cc
  ../../../../unit_tests/test_os.cc
  ../../../../unit_tests/test_path.cc
  ../../../../unit_tests/test_property.cc
  ../../../../unit_tests/test_string.cc
  ../../../../unit_tests/test_table.cc
  ../../../../unit_tests/test_tempo_array.cc
  ../../../../unit_tests/test_thread.cc
  ../../../../unit_tests/test_traits.cc
  ../../../../unit_tests/test_types.cc
  ../../../../unit_tests/unit_test.cc
  ../../../../unit_tests/unit_test.h
  ../../../../unit_tests/using_statement.cc
)

include_directories(../../../../include)

if(CMAKE_BUILD_TYPE MATCHES "debug")
  add_definitions(-D__STDC_LIMIT_MACROS)
  add_definitions(-D__STDC_FORMAT_MACROS)
  add_definitions(-D__STDC_CONSTANT_MACROS)
  add_definitions(-D_DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -MMD -MP -MP -g -Wall -Wextra -fomit-frame-pointer -m64 -std=c++14 -fno-rtti")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -MMD -MP -MP -g -Wall -Wextra -fomit-frame-pointer -m64")
endif()

if(CMAKE_BUILD_TYPE MATCHES "release")
  add_definitions(-DNDEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -MMD -MP -MP -O3 -m64")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -MMD -MP -MP -O3 -m64")
endif()


if(CMAKE_BUILD_TYPE MATCHES "debug")
  add_executable(riku.unit_tests.debug ${source_list})
  target_link_libraries(riku.unit_tests.debug riku.debug)
endif()

if(CMAKE_BUILD_TYPE MATCHES "release")
  add_executable(riku.unit_tests ${source_list})
  target_link_libraries(riku.unit_tests riku)
endif()

