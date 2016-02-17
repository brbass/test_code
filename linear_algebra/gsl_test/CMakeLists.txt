cmake_minimum_required(VERSION 2.8.9)

set(GSL_DIR /home/software/rhel6/gsl/1.15)

set(CMAKE_CXX_FLAGS "-L/home/software/rhel6/gsl/1.15/lib -lgsl -lgslcblas -lm -I/home/software/rhel6/gsl/1.15/include")

project(gsl_test)

file(GLOB SOURCES "src/*.cc")

add_executable(testGsl ${SOURCES})
