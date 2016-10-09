# This file describes build for tests
# Requires Criterion library to run tests

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(xs_tests)

set(CMAKE_CXX_FLAGS "-g -Wall -pedantic")

find_package(PkgConfig)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake")

add_definitions(-std=gnu99)

find_package(Criterion REQUIRED)

add_executable(xs_tests
  ../map.c
  ../tests/test_map.c
)

target_link_libraries(xs_tests
  ${CRITERION_LIBRARIES}
)

include_directories(
  ${CRITERION_INCLUDE_DIRS}
)
