cmake_minimum_required(VERSION 3.3)
project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_module")

set(FREEGLUT_INCLUDE_DIR "E:/gitrepo/freeglut-3.0.0/include")
set(FREEGLUT_LIBRARY "E:/gitrepo/freeglut-3.0.0/include/freeglutd.lib")

set(GLEW_INCLUDE_DIR "E:/gitrepo/glew-2.1.0/include")
set(GLEW_LIBRARY "E:/gitrepo/glew-2.1.0/build/cmake/build/lib/Debug/glew32d.lib")

find_package(FREEGLUT REQUIRED)
#--- Find GLUT
# find_package(GLUT REQUIRED)
# include_directories(${GLUT_INCLUDE_DIRS})
# link_directories(${GLUT_LIBRARY_DIRS})
# add_definitions(${GLUT_DEFINITIONS})
# if(NOT GLUT_FOUND)
#     message(ERROR " GLUT not found!")
# endif(NOT GLUT_FOUND)

find_package(GLEW REQUIRED)

#--- Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)


#--- GL includes
include_directories(
	#"/usr/include/GL"
)

add_executable(test 
	src/test.cpp
	)

target_link_libraries(test 
	${OPENGL_LIBRARIES} 
	${FREEGLUT_LIBRARY} 
	${GLEW_LIBRARARY})
