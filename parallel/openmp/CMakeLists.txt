cmake_minimum_required (VERSION 3.1)

# compiler options
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INSTALL_PREFIX /home/brbass/research/owl/bin)

# standard flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o3 -fopenmp")

# gsl flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/home/software/rhel6/gsl/1.15/lib -lgsl -lgslcblas -I/home/software/rhel6/gsl/1.15/include")

# trilinos flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lepetra -lamesos -laztecoo -lepetraext -ltriutils -lepetra -lteuchosremainder -lteuchosnumerics -lteuchoscomm -lteuchosparameterlist -lteuchoscore -I/usr/cac/rhel6/trilinos/12.0.1/include -L/usr/cac/rhel6/trilinos/12.0.1/lib")

project(Owl)

# enable_testing()

file(GLOB owl_src "src/*.cc")

# set(owl_src src/Check.cc src/Gauss_Legendre.cc src/Ordinates.cc src/Parser.cc src/RBF.cc src/RBF_Basis.cc src/RBF_Sn_Transport.cc)
# set(owl_main src/Owl.cc)
# set(owl_test src/tst_Owl.cc)

include_directories(src)

# add_executable(owl ${owl_src} ${owl_main})
add_executable(tst_owl ${owl_src})

add_test(test_owl tst_owl)

# install(TARGETS owl DESTINATION .)
install(TARGETS tst_owl DESTINATION .)
