cmake_minimum_required(VERSION 3.10)
project(cli)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/*.h"
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

list(REMOVE_ITEM SOURCES
    "${CMAKE_BINARY_DIR}/CMakeFiles/3.28.3/CompilerIdCXX/CMakeCXXCompilerId.cpp"
)

add_executable(cli ${SOURCES})
