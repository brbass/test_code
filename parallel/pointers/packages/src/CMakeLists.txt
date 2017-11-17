set(executable_name pointers)

set(local_include_directories ${global_include_directories} ${global_trilinos_include_directories})
set(local_link_directories ${global_trilinos_link_directories})
set(local_dependencies ${global_trilinos_link_libraries})

file(GLOB src *.cc *.hh)

include_directories(${local_include_directories})
link_directories(${library_link_directories})

add_executable(${executable_name} ${src})
target_link_libraries(${executable_name} ${local_dependencies})
install(TARGETS ${executable_name} DESTINATION ${CMAKE_INSTALL_PREFIX})
