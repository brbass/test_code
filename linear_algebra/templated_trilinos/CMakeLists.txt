cmake_minimum_required(VERSION 3.1)

project(MyProject)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11 -o3")

# Find Trilinos packages

set(TrilinosPackages Teuchos Tpetra Belos)

foreach(TrilinosPackage ${TrilinosPackages})
    find_package(${TrilinosPackage} REQUIRED)
    set(CMAKE_CXX_COMPILER ${${TrilinosPackage}_CXX_COMPILER} )
    set(CMAKE_C_COMPILER ${${TrilinosPackage}_C_COMPILER} )
    set(CMAKE_CXX_FLAGS  "${${TrilinosPackage}_CXX_COMPILER_FLAGS} ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS  "${${TrilinosPackage}_C_COMPILER_FLAGS} ${CMAKE_C_FLAGS}")
    include_directories(${${TrilinosPackage}_INCLUDE_DIRS} ${${TrilinosPackage}_TPL_INCLUDE_DIRS})
    link_directories(${${TrilinosPackage}_LIBRARY_DIRS} ${${TrilinosPackage}_TPL_LIBRARY_DIRS})
endforeach(TrilinosPackage)

# Include source files

include_directories(src)
add_library(mylibrary src/Test_Trilinos.cc src/Test_Trilinos.hh)
add_executable(tst_trilinos "src/main.cc")

# Link libraries

target_link_libraries(tst_trilinos mylibrary)

foreach(TrilinosPackage ${TrilinosPackages})
    target_link_libraries(tst_trilinos ${${TrilinosPackage}_LIBRARIES} ${${TrilinosPackage}_TPL_LIBRARIES})
endforeach(TrilinosPackage)
