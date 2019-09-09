cmake_minimum_required(VERSION 3.3)
project(computer_graphics_lecture)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_module")

if(WIN32)
	set(CMAKE_PREFIX_PATH "e:/gitrepo/freeglut-3.0.0/")
	set(CMAKE_LIBRARY_PATH "e:/gitrepo/freeglut-3.0.0/build/lib/Release/")
endif(WIN32)

#--- Find GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
	message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)


if(WIN32)
	set(CMAKE_PREFIX_PATH "e:/gitrepo/glew-2.1.0/")
	set(CMAKE_LIBRARY_PATH "e:/gitrepo/glew-2.1.0/build/cmake/build/lib/Release/")
endif(WIN32)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	link_libraries(${GLEW_LIBRARIES})
endif()

if(WIN32)
	set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/GLFW/lib/cmake/glfw3")
	set(CMAKE_LIBRARY_PATH "C:/Program Files (x86)/GLFW/lib")
endif(WIN32)

#--- Find GLFW
find_package(glfw3 REQUIRED)
if (glfw3_FOUND)
	if(WIN32)
		include_directories("C:/Program Files (x86)/GLFW/include")
		link_libraries("C:/Program Files (x86)/GLFW/lib")
		set(glfw3_LIBRARIES "C:/Program Files (x86)/GLFW/lib/glfw3.lib")
	else()
		include_directories(${glfw3_INCLUDE_DIRS})
		link_libraries(${glfw3_LIBRARIES})
	endif()
endif()

#--- Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
	message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_executable(cg1 
	src/cg1.cpp
	)
add_executable(cg2 
	src/cg2.cpp
	)
add_executable(cg_week3
	src/cg_week3.cpp
	)

message(STATUS "[+]" ${FREEGLUT_LIBRARIES})

if(WIN32)
	target_link_libraries(cg1 
		${OPENGL_LIBRARIES} 
		${FREEGLUT_LIBRARIES} 
		${GLEW_LIBRARIES}
		)
	target_link_libraries(cg2 
		${OPENGL_LIBRARIES} 
		${FREEGLUT_LIBRARIES} 
		${GLEW_LIBRARIES}
		${glfw3_LIBRARIES}
		)
	target_link_libraries(cg_week3
		${OPENGL_LIBRARIES} 
		${FREEGLUT_LIBRARIES} 
		${GLEW_LIBRARIES}
		${glfw3_LIBRARIES}
		)
else()
	target_link_libraries(cg1 
		${OPENGL_LIBRARIES} 
		${GLUT_LIBRARIES} 
		${GLEW_LIBRARIES}
		)
	target_link_libraries(cg2 
		${OPENGL_LIBRARIES} 
		${GLUT_LIBRARIES} 
		${GLEW_LIBRARIES}
		glfw
		)
	target_link_libraries(cg_week3
		${OPENGL_LIBRARIES} 
		${GLUT_LIBRARIES} 
		${GLEW_LIBRARIES}
		glfw
		)
endif()

