cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
  )

add_executable(convolution
  src/convolution.cpp
  )
target_link_libraries(convolution
  ${OpenCV_LIBS}
  ${EIGEN3_LIBS}
  )

