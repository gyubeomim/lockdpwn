cmake_minimum_required(VERSION 2.8)
project(g2o_examples)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/thirdparty/g2o/cmake_modules)


include_directories(
	${PROJECT_SOURCE_DIR}/thirdparty/g2o
	)
add_subdirectory(thirdparty/g2o)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(circle_fitting
	src/circle_fitting.cpp
	)

target_link_libraries(circle_fitting
	${EIGEN3_LIBS}
	${OpenCV_LIBS}
	g2o
	)

add_executable(slam_toy_example
	src/slam_toy_example.cpp)

target_link_libraries(slam_toy_example
	${EIGEN3_LIBS}
	${OpenCV_LIBS}
	g2o
	)
