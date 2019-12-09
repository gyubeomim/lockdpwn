cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(CylinderExample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(VTK 6 REQUIRED)

message (STATUS "VTK_VERSION: ${VTK_VERSION}")

if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(CylinderExample
    MACOSX_BUNDLE
    src/CylinderExample.cxx
    )
  target_link_libraries(CylinderExample
    PRIVATE
    ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(CylinderExample
    MACOSX_BUNDLE
    src/CylinderExample.cxx
    )
  target_link_libraries(CylinderExample
    PRIVATE
    ${VTK_LIBRARIES}
    )
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS CylinderExample
    MODULES ${VTK_LIBRARIES}
    )
endif ()
