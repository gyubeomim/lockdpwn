cmake_minimum_required(VERSION 3.5)
project(eigen_test)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIRS})

#------------------------------------
add_executable(eigen_test 
 	src/eigen_test.cc
)
target_link_libraries(eigen_test 
  ${EIGEN3_LIBS}
)

#------------------------------------
#add_executable(quaternion_test 
# 	src/quaternion_test.cc
#)
#target_link_libraries(quaternion_test 
#  ${EIGEN3_LIBS}
#)

#------------------------------------
add_executable(rotmat_to_quat
	src/rotmat_to_quat.cc
)
target_link_libraries(rotmat_to_quat
 ${EIGEN3_LIBS}
)

#------------------------------------
add_executable(trans_accumulator
	src/trans_accumulator.cc
)
target_link_libraries(trans_accumulator
 ${EIGEN3_LIBS}
)
