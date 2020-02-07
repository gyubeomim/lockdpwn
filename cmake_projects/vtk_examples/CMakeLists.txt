cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(CylinderExample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(VTK 6 REQUIRED)

message (STATUS "VTK_VERSION: ${VTK_VERSION}")

include(${VTK_USE_FILE})

# CylinderExample
add_executable(CylinderExample
  MACOSX_BUNDLE
  src/CylinderExample.cxx
  )
target_link_libraries(CylinderExample
  PRIVATE
  ${VTK_LIBRARIES}
  )

# HighlightSelectedPoints
add_executable(HighlightSelectedPoints
  MACOSX_BUNDLE
  src/HighlightSelectedPoints.cxx
  )
target_link_libraries(HighlightSelectedPoints
  PRIVATE
  ${VTK_LIBRARIES}
  )


# =========================We're currently using vtk 6.x.==============================
# if (NOT VTK_VERSION VERSION_LESS "8.90.0")
#   # vtk_module_autoinit is needed, if VTK version is > 8.9
#   vtk_module_autoinit(
#     TARGETS CylinderExample
#     MODULES ${VTK_LIBRARIES}
#     )
# endif ()
