cmake_minimum_required(VERSION 2.8)
project(g2o_examples)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(g2o REQUIRED)
include_directories(
  ${G2O_INCLUDE_DIRS}
  )

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(curve_fitting
  src/curve_fitting.cpp)

target_link_libraries(curve_fitting
  g2o_core
  g2o_stuff
  ${EIGEN3_LIBRARIES}
  ${OpenCV_LIBS}
  )

add_executable(slam_toy_example
  src/slam_toy_example.cpp)

target_link_libraries(slam_toy_example
  g2o_core
  g2o_stuff
  ${EIGEN3_LIBRARIES}
  ${OpenCV_LIBS}
  )
