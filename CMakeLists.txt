#basic setting
cmake_minimum_required(VERSION 3.2.2)
project(raytracing C CXX)
set(CMAKE_BUILD_TYPE Debug)

#binary dir/ output file
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/out)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#global include
set(GLOBAL_DIR ${PROJECT_SOURCE_DIR})
#set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
#include_directories("${PROJECT_INCLUDE_DIR}")
#include_directories("${PROJECT_SOURCE_DIR}")

#subproject setting
add_subdirectory(rtMathLib)
add_subdirectory(1-1-image)
add_subdirectory(1-3-ray)
add_subdirectory(1-5-hit)
add_subdirectory(1-8-metal)
add_subdirectory(1-9-dielectric)
add_subdirectory(1-final)