cmake_minimum_required (VERSION 3.1)

project(LU_Test)

# compiler options
set(CMAKE_C_COMPILER "mpicc")
set(CMAKE_CXX_COMPILER "mpic++")
set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_BUILD_TYPE Debug)

# standard flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o3")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/../bin)

# gsl flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/usr/local/Cellar/gsl/1.16/lib -lgsl -lgslcblas -I/usr/local/Cellar/gsl/1.16/include")

# trilinos flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lepetra -lamesos -laztecoo -lepetraext -ltriutils -lepetra -lteuchosremainder -lteuchosnumerics -lteuchoscomm -lteuchosparameterlist -lteuchoscore -I/usr/local/Cellar/trilinos/12.4.2_1/include -L/usr/local/Cellar/trilinos/12.4.2_1/lib")

file(GLOB SOURCES "src/*.cc" "lib/*.c" "lib/*.cpp")

include_directories(src lib)

add_executable(lu_test ${SOURCES})


