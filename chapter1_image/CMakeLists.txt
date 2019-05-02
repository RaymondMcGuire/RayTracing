#chapter1 config
cmake_minimum_required(VERSION 3.2.2)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories("${GLOBAL_DIR}/extlib")
include_directories("${LIBRARY_OUTPUT_PATH}")
file(GLOB_RECURSE CHAPTER1_FILES
	"${PROJECT_INCLUDE_DIR}/*.h"
	"${PROJECT_SOURCE_DIR}/*.cpp"
)

add_executable(cpt1 ${CHAPTER1_FILES})
target_link_libraries(cpt1 rkMathLib)