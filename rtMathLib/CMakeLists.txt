cmake_minimum_required(VERSION 3.2.2)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE rtMathLib_FILES
	"${PROJECT_INCLUDE_DIR}/*.h"
	"${PROJECT_SOURCE_DIR}/*.cpp"
)

add_library(rkMathLib STATIC ${rtMathLib_FILES})
target_include_directories(rkMathLib PUBLIC ${PROJECT_INCLUDE_DIR})
