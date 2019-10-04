cmake_minimum_required(VERSION 3.5)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

find_package(Eigen3 3.1.0 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIRS})

add_executable(eigen_test eigen_test.cpp)

target_link_libraries(eigen_test ${EIGEN3_LIBS})
