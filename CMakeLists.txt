cmake_minimum_required(VERSION 3.10)
project(cli)

set(CMAKE_CXX_STANDARD 17)

set(CLANG_TIDY_CHECKS "*,-llvm-header-guard,-modernize-use-trailing-return-type,-google-runtime-references,readability-identifier-naming,readability-braces-around-statements,readability-const-return-type,modernize-use-nullptr,modernize-pass-by-value,performance-inefficient-vector-operation,performance-move-const-arg,bugprone-dangling-handle,bugprone-incorrect-pointer-arithmetic,clang-analyzer-core,clang-analyzer-unix.Malloc,misc-const-correctness,misc-non-private-member-variables-in-classes,cppcoreguidelines-avoid-c-arrays,cppcoreguidelines-pro-type-static-cast")

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
