#######################################################
# Get the directories for all header files in project #
#######################################################

macro(header_directories return_list)
    file(GLOB_RECURSE header_files *.hh)
    set(header_directories "")
    foreach(header_file ${header_files})
        get_filename_component(header_directory ${header_file} DIRECTORY)
        set(header_directories ${header_directories} ${header_directory})
    endforeach()
    list(REMOVE_DUPLICATES header_directories)
    set(${return_list} ${header_directories})
endmacro()

header_directories(header_directories)
set(global_include_directories ${header_directories} CACHE INTERNAL "global_include_directories")

set(subdirectories math problem)

foreach(subdirectory ${subdirectories})
    message("${subdirectory}")
    add_subdirectory(${subdirectory})
endforeach(subdirectory)

