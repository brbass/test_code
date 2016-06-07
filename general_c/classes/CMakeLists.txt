cmake_minimum_required (VERSION 3.1)

project(Classes)

# compiler options
set(CMAKE_C_COMPILER "mpicc")
set(CMAKE_CXX_COMPILER "mpic++")
set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_BUILD_TYPE Debug)

# standard flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o3")
# set(CMAKE_INSTALL_PREFIX /home/brbass/research/test_code/general_c/assert/bin)

# gsl flags
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/home/software/rhel6/gsl/1.15/lib -lgsl -lgslcblas -I/home/software/rhel6/gsl/1.15/include")

# trilinos flags
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lepetra -lamesos -laztecoo -lepetraext -ltriutils -lepetra -lteuchosremainder -lteuchosnumerics -lteuchoscomm -lteuchosparameterlist -lteuchoscore -I/usr/cac/rhel6/trilinos/12.0.1/include -L/usr/cac/rhel6/trilinos/12.0.1/lib")

# enable_testing()

file(GLOB SOURCES "src/*.cc")

include_directories(src)

add_executable(classes ${SOURCES})

# install(TARGETS classes DESTINATION .)

