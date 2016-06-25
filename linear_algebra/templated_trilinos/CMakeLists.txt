cmake_minimum_required (VERSION 3.1)

# set(Trilinos_PREFIX /usr/cac/rhel6/trilinos/12.0.1)
# set(CMAKE_PREFIX_PATH ${Trilinos_PREFIX} ${CMAKE_PREFIX_PATH})

Project(Test_Trilinos)

find_package(Trilinos REQUIRED)
MESSAGE("\nFound Trilinos!  Here are the details: ")
MESSAGE("   Trilinos_DIR = ${Trilinos_DIR}")
MESSAGE("   Trilinos_VERSION = ${Trilinos_VERSION}")
MESSAGE("   Trilinos_PACKAGE_LIST = ${Trilinos_PACKAGE_LIST}")
MESSAGE("   Trilinos_LIBRARIES = ${Trilinos_LIBRARIES}")
MESSAGE("   Trilinos_INCLUDE_DIRS = ${Trilinos_INCLUDE_DIRS}")
MESSAGE("   Trilinos_LIBRARY_DIRS = ${Trilinos_LIBRARY_DIRS}")
MESSAGE("   Trilinos_TPL_LIST = ${Trilinos_TPL_LIST}")
MESSAGE("   Trilinos_TPL_INCLUDE_DIRS = ${Trilinos_TPL_INCLUDE_DIRS}")
MESSAGE("   Trilinos_TPL_LIBRARIES = ${Trilinos_TPL_LIBRARIES}")
MESSAGE("   Trilinos_TPL_LIBRARY_DIRS = ${Trilinos_TPL_LIBRARY_DIRS}")
MESSAGE("   Trilinos_BUILD_SHARED_LIBS = ${Trilinos_BUILD_SHARED_LIBS}")
MESSAGE("End of Trilinos details\n")


# find_package(Anasazi REQUIRED)
# find_package(Belos REQUIRED)
# find_package(Teuchos REQUIRED)
# find_package(Tpetra REQUIRED)
# find_package( REQUIRED)
# find_package( REQUIRED)

# project(Test_Trilinos)

# file(GLOB SOURCES "src/*.cc")

# include_directories(src)

# add_executable(tst_trilinos ${SOURCES})

# install(TARGETS tst_trilinos DESTINATION .)

