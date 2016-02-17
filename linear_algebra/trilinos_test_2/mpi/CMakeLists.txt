cmake_minimum_required(VERSION 3.0)

project(test)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

add_executable(mpi_test mpi_test.cc)
target_link_libraries(mpi_test ${MPI_LIBRARIES})
