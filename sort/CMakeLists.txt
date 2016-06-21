cmake_minimum_required (VERSION 3.1)

project(KD_Sort)

# compiler options
set(CMAKE_C_COMPILER "mpicc")
set(CMAKE_CXX_COMPILER "mpic++")
set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_BUILD_TYPE Debug)

# standard flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o3")

# nanoflann flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/Users/brbass/Documents/research/code/test_code/sort/nanoflann/include")

# enable_testing()

file(GLOB SOURCES "src/*.cc")

include_directories(src)

add_executable(kd_sort ${SOURCES})


