find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})
add_executable(test test.cpp)
target_link_libraries(test ${CERES_LIBRARIES})
