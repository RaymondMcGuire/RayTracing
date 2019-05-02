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
add_subdirectory(chapter1_image)
add_subdirectory(chapter3_ray)
add_subdirectory(chapter5_hit)
add_subdirectory(chapter8_metal)
add_subdirectory(chapter9_dielectric)
add_subdirectory(final)