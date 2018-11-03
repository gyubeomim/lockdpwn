# Ceres Solver - A fast non-linear least squares minimizer
# Copyright 2015 Google Inc. All rights reserved.
# http://ceres-solver.org/
#
# if (BUILD_SHARED_LIBS)
#   remove_definitions(-DCERES_BUILDING_SHARED_LIBRARY)
# endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(helloworld helloworld.cc)
target_link_libraries(helloworld ceres glog)

# Force CMake to link curve_fitting_c using the C linker, this is important
# when Ceres was compiled using C++11 to ensure that -std=c++11 is not passed
# through.
# set_target_properties(curve_fitting_c PROPERTIES LINKER_LANGUAGE C)
# As this is a C file #including <math.h> we have to explicitly add the math
# library (libm). Although some compilers (dependent upon options) will accept
# the indirect link to libm via Ceres, at least GCC 4.8 on pure Debian won't.
