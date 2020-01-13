cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

project(opencv_test)

find_package( OpenCV REQUIRED )
find_package( Eigen3 REQUIRED )

include_directories(${EIGEN3_INCLUDE_DIRS})

add_executable(test_cv
  src/test_cv.cpp
  )
target_link_libraries(test_cv
  ${OpenCV_LIBS}
  )

add_executable(test_access
  src/test_access.cpp
  )
target_link_libraries(test_access
  ${OpenCV_LIBS}
  ${EIGEN3_LIBS}
  )

add_executable(disparity
  src/disparity.cpp
  )
target_link_libraries(disparity
  ${OpenCV_LIBS}
  ${EIGEN3_LIBS}
  )

add_executable(findchessboard
  src/findchessboard.cpp
  )
target_link_libraries(findchessboard
  ${OpenCV_LIBS}
  )

add_executable(extract_rgb
  src/extract_rgb.cpp
  )
target_link_libraries(extract_rgb
  ${OpenCV_LIBS}
  )

add_executable(morphology
  src/morphology.cpp
  )
target_link_libraries(morphology
  ${OpenCV_LIBS}
  )

add_executable(demo
  src/demo.cpp
  )
target_link_libraries(demo
  ${OpenCV_LIBS}
  )
