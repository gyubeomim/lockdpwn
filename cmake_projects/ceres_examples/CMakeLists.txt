cmake_minimum_required(VERSION 2.8)
project(ceres_examples)

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(helloworld
  src/helloworld.cc)

target_link_libraries(helloworld
  ${CERES_LIBRARIES}
  )
