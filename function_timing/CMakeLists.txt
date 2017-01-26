cmake_minimum_required (VERSION 3.1)

###########
# Project #
###########

project(Functions)

####################
# Compiler options #
####################

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o3")

if(TRUE)
    message("\tCMake CXX Compiler:\t${CMAKE_CXX_COMPILER}")
    message("\tCMake C Compiler:\t${CMAKE_C_COMPILER}")
    message("\tCMake CXX Flags:\t${CMAKE_CXX_FLAGS}")
    message("\tCMake C Flags:\t${CMAKE_C_FLAGS}")
endif()

########################
# Include source files #
########################

file(GLOB SRC "src/*.cc" "lib/*.cc")
include_directories(src lib)

##################
# Add executable #
##################

add_executable(functions ${SRC})

install(TARGETS functions DESTINATION .)
