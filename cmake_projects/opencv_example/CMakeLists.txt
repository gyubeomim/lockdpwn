cmake_minimum_required(VERSION 2.8)

project(opencv_test)

find_package( OpenCV REQUIRED )
find_package( Eigen3 REQUIRED )

include_directories(${EIGEN3_INCLUDE_DIRS})

add_executable(test
  src/test.cpp
  )
target_link_libraries(test
  ${OpenCV_LIBS}
  )

add_executable(test_access
  src/test_access.cpp
  )
target_link_libraries(test_access
  ${OpenCV_LIBS}
  ${EIGEN3_LIBS}
  )
