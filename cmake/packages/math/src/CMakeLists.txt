include_directories(${global_include_directories})

file(GLOB math_src *.cc *.hh)
add_library(math ${math_src})
install(TARGETS math DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
