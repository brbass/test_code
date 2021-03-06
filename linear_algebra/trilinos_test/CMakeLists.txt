cmake_minimum_required(VERSION 2.8)

SET(CMAKE_PREFIX_PATH ${Trilinos_PREFIX} ${CMAKE_PREFIX_PATH})

FIND_PACKAGE(Trilinos REQUIRED)

# MESSAGE("\nFound Trilinos!  Here are the details: ")
# MESSAGE("   Trilinos_DIR = ${Trilinos_DIR}")
# MESSAGE("   Trilinos_VERSION = ${Trilinos_VERSION}")
# MESSAGE("   Trilinos_PACKAGE_LIST = ${Trilinos_PACKAGE_LIST}")
# MESSAGE("   Trilinos_LIBRARIES = ${Trilinos_LIBRARIES}")
# MESSAGE("   Trilinos_INCLUDE_DIRS = ${Trilinos_INCLUDE_DIRS}")
# MESSAGE("   Trilinos_LIBRARY_DIRS = ${Trilinos_LIBRARY_DIRS}")
# MESSAGE("   Trilinos_TPL_LIST = ${Trilinos_TPL_LIST}")
# MESSAGE("   Trilinos_TPL_INCLUDE_DIRS = ${Trilinos_TPL_INCLUDE_DIRS}")
# MESSAGE("   Trilinos_TPL_LIBRARIES = ${Trilinos_TPL_LIBRARIES}")
# MESSAGE("   Trilinos_TPL_LIBRARY_DIRS = ${Trilinos_TPL_LIBRARY_DIRS}")
# MESSAGE("   Trilinos_BUILD_SHARED_LIBS = ${Trilinos_BUILD_SHARED_LIBS}")
# MESSAGE("End of Trilinos details\n")

# Make sure to use same compilers and flags as Trilinos
SET(CMAKE_CXX_COMPILER ${Trilinos_CXX_COMPILER} )
SET(CMAKE_C_COMPILER ${Trilinos_C_COMPILER} )
SET(CMAKE_Fortran_COMPILER ${Trilinos_Fortran_COMPILER} )

SET(CMAKE_CXX_FLAGS  "${Trilinos_CXX_COMPILER_FLAGS} ${CMAKE_CXX_FLAGS}")
SET(CMAKE_C_FLAGS  "${Trilinos_C_COMPILER_FLAGS} ${CMAKE_C_FLAGS}")
SET(CMAKE_Fortran_FLAGS  "${Trilinos_Fortran_COMPILER_FLAGS} ${CMAKE_Fortran_FLAGS}")

PROJECT(Test_Trilinos)

ADD_DEFINITIONS(-DMYAPP_EPETRA)

INCLUDE_DIRECTORIES(${Trilinos_INCLUDE_DIRS} ${Trilinos_TPL_INCLUDE_DIRS})
LINK_DIRECTORIES(${Trilinos_LIBRARY_DIRS} ${Trilinos_TPL_LIBRARY_DIRS})

INCLUDE_DIRECTORIES(src)

ADD_LIBRARY(test_trilinos_library src/test_trilinos.cc)

ADD_EXECUTABLE(tst_trilinos src/main.cc)

TARGET_LINK_LIBRARIES(tst_trilinos  test_trilinos_library  ${Trilinos_LIBRARIES} ${Trilinos_TPL_LIBRARIES}) 

# enable_testing()
# add_test(NAME MyTest COMMAND tst_trilinos)
