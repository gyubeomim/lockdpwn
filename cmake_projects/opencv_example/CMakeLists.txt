cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

project(opencv_test)

find_package( OpenCV REQUIRED )
find_package( Eigen3 REQUIRED )

include_directories(${EIGEN3_INCLUDE_DIRS})

add_executable(test
  src/test.cc
  )
target_link_libraries(test
  ${OpenCV_LIBS}
  )

add_executable(cv_mat_access
  src/cv_mat_access.cc
  )
target_link_libraries(cv_mat_access
  ${OpenCV_LIBS}
  ${EIGEN3_LIBS}
  )

add_executable(disparity
  src/disparity.cc
  )
target_link_libraries(disparity
  ${OpenCV_LIBS}
  ${EIGEN3_LIBS}
  )

add_executable(findchessboard
  src/findchessboard.cc
  )
target_link_libraries(findchessboard
  ${OpenCV_LIBS}
  )

add_executable(extract_rgb
  src/extract_rgb.cc
  )
target_link_libraries(extract_rgb
  ${OpenCV_LIBS}
  )

add_executable(morphology
  src/morphology.cc
  )
target_link_libraries(morphology
  ${OpenCV_LIBS}
  )

add_executable(demo
  src/demo.cc
  )
target_link_libraries(demo
  ${OpenCV_LIBS}
  )

add_executable(patch_comparison
  src/patch_comparison.cc
  )
target_link_libraries(patch_comparison
  ${OpenCV_LIBS}
  )
