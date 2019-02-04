find_package(Ceres REQUIRED)
add_executable(test test.cpp)
target_link_libraries(test ceres)
