cmake_minimum_required(VERSION 2.8)

project(opencv_test)

find_package( OpenCV REQUIRED )

add_executable(test src/test.cpp )
target_link_libraries(test ${OpenCV_LIBS} )
