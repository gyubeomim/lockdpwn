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

add_library(matblib
 src/mathlib.cc
 )
target_link_libraries(mathlib
	${EIGEN3_LIBS}
  )
