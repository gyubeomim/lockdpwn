cmake_minimum_required(VERSION 2.6)
#set(BUILD_TYPE Release)
#set(BUILD_TYPE RelWithDebInfo)

set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)
#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

#find_package(OpenCV 2.4 REQUIRED )
find_package(OpenCV 3. REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(Eigen3 REQUIRED)
include_directories( ${EIGEN3_INCLUDE_DIR} )

find_package(Sophus REQUIRED) # https://github.com/strasdat/Sophus
if(Sophus_FOUND)
    #message("Sophus Found")
    #message(${Sophus_INCLUDE_DIRS}) # Doesn't work
    include_directories(${Sophus_INCLUDE_DIRS})
    # Copy CMake/SophusConfig.cmake.in to Sophus dir. and re install
endif()



find_package(Boost COMPONENTS filesystem regex)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# flags
add_definitions("-DENABLE_SSE")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS
    #-std=c++0x
    #"${SSE_FLAGS} -O3 -g -std=c++0x -march=native"
    #"${SSE_FLAGS} -O3 -g -std=c++0x -fno-omit-frame-pointer"
)


add_definitions(-DRESOURCE="${CMAKE_SOURCE_DIR}/../resource")
include_directories("${CMAKE_SOURCE_DIR}//include")

if(Boost_FOUND)
    add_executable(direct_test
        ${CMAKE_SOURCE_DIR}/include/direct.h
        ${CMAKE_SOURCE_DIR}/include/intrinsic.h

        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/optimizer.cpp
        ${CMAKE_SOURCE_DIR}/src/direct.cpp
        ${CMAKE_SOURCE_DIR}/src/direct_types.cpp
        ${CMAKE_SOURCE_DIR}/src/img_process.cpp
        ${CMAKE_SOURCE_DIR}/src/distortion.cpp # distorted directed method
        ${CMAKE_SOURCE_DIR}/src/intrinsic.cpp
        ${CMAKE_SOURCE_DIR}/src/graph_test.cpp
        )

    target_link_libraries(direct_test
        ${OpenCV_LIBS} ${Boost_LIBRARIES}
        )
endif()

