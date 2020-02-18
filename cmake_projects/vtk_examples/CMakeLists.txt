cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(CylinderExample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(VTK REQUIRED)

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

# PointPicker
add_executable(PointPicker
  MACOSX_BUNDLE
  src/PointPicker.cxx
  )
target_link_libraries(PointPicker
  PRIVATE
  ${VTK_LIBRARIES}
  )

# SelectAVertex
add_executable(SelectAVertex
  MACOSX_BUNDLE
  src/SelectAVertex.cxx
  )
target_link_libraries(SelectAVertex
  PRIVATE
  ${VTK_LIBRARIES}
  )
