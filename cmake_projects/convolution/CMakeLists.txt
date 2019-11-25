cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(convolution
  src/convolution.cpp
  )
target_link_libraries(convolution
  ${OpenCV_LIBS}
  )

