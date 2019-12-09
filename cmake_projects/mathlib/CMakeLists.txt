cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(mathlib)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Eigen3 REQUIRED)


if(WIN32)
	message(STATUS $ENV{EIGEN3_INCLUDE_DIRS})
	include_directories(
		include
		$ENV{EIGEN3_INCLUDE_DIRS}
		)
else()
	include_directories(
		include
		${EIGEN3_INCLUDE_DIRS}
		)
endif()

add_library(mathlib
	src/mathlib.cc
	src/so3.cc
	src/rotation_matrix.cc
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
