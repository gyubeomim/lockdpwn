cmake_minimum_required(VERSION 2.4)

add_compile_options(-std=c++11)

add_executable(pure_virtual_class
  src/pure_virtual_class.cpp
  )
target_link_libraries(pure_virtual_class
  )

