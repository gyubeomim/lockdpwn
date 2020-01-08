cmake_minimum_required(VERSION 3.5)
project(eigen_test)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIRS})

add_executable(eigen_test 
 	src/eigen_test.cpp
)
target_link_libraries(eigen_test 
  ${EIGEN3_LIBS}
)

#add_executable(quaternion_test 
# 	src/quaternion_test.cpp
#)
#target_link_libraries(quaternion_test 
#  ${EIGEN3_LIBS}
#)

add_executable(rotmat_to_quat
	src/rotmat_to_quat.cpp
)
target_link_libraries(rotmat_to_quat
 ${EIGEN3_LIBS}
)
