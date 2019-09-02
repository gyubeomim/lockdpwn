cmake_minimum_required(VERSION 3.3)
project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_module")

# set(FREEGLUT_INCLUDE_DIR "E:/gitrepo/freeglut-3.0.0/include")
# set(FREEGLUT_LIBRARY "E:/gitrepo/freeglut-3.0.0/build/lib/Debug/freeglutd.lib")
# set(FREEGLUT_LIBRARIES "E:/gitrepo/freeglut-3.0.0/build/lib/Debug")


# set(GLEW_INCLUDE_DIR "E:/gitrepo/glew-2.1.0/include")
# set(GLEW_LIBRARY "E:/gitrepo/glew-2.1.0/build/cmake/build/lib/Debug/glew32d.lib")
# set(GLEW_LIBRARIES "E:/gitrepo/glew-2.1.0/build/cmake/build/lib/Debug")

set(CMAKE_PREFIX_PATH "e:/gitrepo/freeglut-3.0.0/")
set(CMAKE_LIBRARY_PATH "e:/gitrepo/freeglut-3.0.0/build/lib/Release/")
# set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/freeglut/bin")
# set(CMAKE_LIBRARY_PATH "C:/Program Files (x86)/freeglut/lib")
# find_package(FREEGLUT 3.0.0 REQUIRED)
# if (FREEGLUT_FOUND)
# 	message(STATUS "[+] " ${FREEGLUT_INCLUDE_DIRS})
# 	include_directories(${FREEGLUT_INCLUDE_DIRS})
# 	message(STATUS "[++] " ${FREEGLUT_LIBRARIES})
# 	link_directories(${FREEGLUT_LIBRARIES})
# endif()

#--- Find GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
message(STATUS "[+] " ${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
message(STATUS "[++] " ${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)


set(CMAKE_PREFIX_PATH "e:/gitrepo/glew-2.1.0/")
set(CMAKE_LIBRARY_PATH "e:/gitrepo/glew-2.1.0/build/cmake/build/lib/Release/")
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
	message(STATUS "[+] " ${GLEW_INCLUDE_DIRS})
    include_directories(${GLEW_INCLUDE_DIRS})
	message(STATUS "[++] " ${GLEW_LIBRARIES})
    link_libraries(${GLEW_LIBRARIES})
endif()

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
	# "e:/gitrepo/freeglut-3.0.0/include/"
)

add_executable(test 
	src/test.cpp
	)

target_link_libraries(test 
	${OPENGL_LIBRARIES} 
	${FREEGLUT_LIBRARIES} 
	${GLEW_LIBRARIES}
	)
