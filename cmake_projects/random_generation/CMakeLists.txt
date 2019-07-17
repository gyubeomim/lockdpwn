cmake_minimum_required(VERSION 2.6)

add_compile_options("-std=c++11")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

project(random_generation)

# include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
# link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

add_executable(random_generation random_generation.cpp)
