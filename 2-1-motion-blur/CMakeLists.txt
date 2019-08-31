#2-1-motion-blur config
cmake_minimum_required(VERSION 3.2.2)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories("${GLOBAL_DIR}/extlib")
include_directories("${LIBRARY_OUTPUT_PATH}")
file(GLOB_RECURSE CHAPTER21_FILES
	"${PROJECT_INCLUDE_DIR}/*.h"
	"${PROJECT_SOURCE_DIR}/*.cpp"
)

add_executable(2-1 ${CHAPTER21_FILES})
target_link_libraries(2-1 rkMathLib)