cmake_minimum_required(VERSION 3.5)

find_package(Eigen3 REQUIRED)

include_directories(${EIGEN_INCLUDE_DIRS})

add_executable(eigen_test eigen_test.cpp)

target_link_libraries(eigen_test ${EIGEN_LIBRARIES})
