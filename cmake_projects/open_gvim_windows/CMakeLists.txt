cmake_minimum_required(VERSION 2.8)

project(opengvim)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(${CMAKE_BUILD_TYPE} "Release")

add_executable(opengvim
  opengvim.cpp
  )
target_link_libraries(opengvim
  )
