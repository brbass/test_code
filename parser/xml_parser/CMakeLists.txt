cmake_minimum_required (VERSION 3.1)

# compiler options
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INSTALL_PREFIX /home/brbass/research/test/serialization/bin)

# standard flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o3")

# project
project(XML_Parser)

# enable_testing()

file(GLOB SOURCES_ "src/*.cc" "lib/*.cpp")

include_directories(src lib)

add_executable(xml_parser ${SOURCES_})

install(TARGETS xml_parser DESTINATION .)
