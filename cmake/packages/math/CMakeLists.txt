set(subdirectories src test)

foreach(subdirectory ${subdirectories})
    add_subdirectory(${subdirectory})
endforeach(subdirectory)
