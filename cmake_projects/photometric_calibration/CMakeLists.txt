cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11)

project(photometric_calibration)

include_directories(
  /usr/include/flycapture/
  )

add_executable(photometric_calibration
  src/photometric_calibration.cpp
  )
target_link_libraries(photometric_calibration
  /usr/lib/libflycapture.so
  )
