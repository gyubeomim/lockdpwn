cmake_minimum_required(VERSION 2.8)

project(mathlib)

include_directories(
    include
    )

add_library(matblib
 src/mathlib.cc
 )
target_link_libraries(mathlib
  )
