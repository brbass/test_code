
foreach(directory ${global_include_directories})
include_directories("${directory}")
message("${directory}")
endforeach()

add_executable(tst_Add tst_Add.cc)
target_link_libraries(tst_Add math)
add_test(Add_test tst_Add)
