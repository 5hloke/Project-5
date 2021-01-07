cmake_minimum_required(VERSION 3.5)
project(P4_2 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DEQUE_SOURCE
  Deque.hpp Deque.txx)

set(XO_SOURCE
  XO.hpp XO.cpp)

set(BOARDXO_SOURCE
  BoardXO.hpp)

set(TEST_SOURCE
  student_tests.cpp)

set(SOURCE ${DEQUE_SOURCE} ${XO_SOURCE} ${BOARDXO_SOURCE})

# create unittests
add_executable(student-tests catch.hpp student_catch.cpp ${SOURCE} ${TEST_SOURCE})

# some simple tests
enable_testing()
add_test(student-tests student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  XO.hpp XO.cpp BoardXO.hpp Deque.hpp Deque.txx student_tests.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
