cmake_minimum_required(VERSION 2.8)

project(mathlib)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Eigen3 REQUIRED)

include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
  )

add_library(mathlib
  src/mathlib.cc
  src/so3.cc
  )
target_link_libraries(mathlib
  ${EIGEN3_LIBS}
  )

#executable--------------------------------------
add_executable(mathlib_test
  src/test/mathlib_test.cc
  )
target_link_libraries(mathlib_test
  ${EIGEN3_LIBS}
  mathlib
  )
