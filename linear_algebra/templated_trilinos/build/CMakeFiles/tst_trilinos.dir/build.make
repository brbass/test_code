# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.5.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.5.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/build

# Include any dependencies generated for this target.
include CMakeFiles/tst_trilinos.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tst_trilinos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tst_trilinos.dir/flags.make

CMakeFiles/tst_trilinos.dir/src/main.cc.o: CMakeFiles/tst_trilinos.dir/flags.make
CMakeFiles/tst_trilinos.dir/src/main.cc.o: ../src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tst_trilinos.dir/src/main.cc.o"
	mpic++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tst_trilinos.dir/src/main.cc.o -c /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/src/main.cc

CMakeFiles/tst_trilinos.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tst_trilinos.dir/src/main.cc.i"
	mpic++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/src/main.cc > CMakeFiles/tst_trilinos.dir/src/main.cc.i

CMakeFiles/tst_trilinos.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tst_trilinos.dir/src/main.cc.s"
	mpic++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/src/main.cc -o CMakeFiles/tst_trilinos.dir/src/main.cc.s

CMakeFiles/tst_trilinos.dir/src/main.cc.o.requires:

.PHONY : CMakeFiles/tst_trilinos.dir/src/main.cc.o.requires

CMakeFiles/tst_trilinos.dir/src/main.cc.o.provides: CMakeFiles/tst_trilinos.dir/src/main.cc.o.requires
	$(MAKE) -f CMakeFiles/tst_trilinos.dir/build.make CMakeFiles/tst_trilinos.dir/src/main.cc.o.provides.build
.PHONY : CMakeFiles/tst_trilinos.dir/src/main.cc.o.provides

CMakeFiles/tst_trilinos.dir/src/main.cc.o.provides.build: CMakeFiles/tst_trilinos.dir/src/main.cc.o


CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o: CMakeFiles/tst_trilinos.dir/flags.make
CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o: ../src/Test_Tpetra.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o"
	mpic++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o -c /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/src/Test_Tpetra.cc

CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.i"
	mpic++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/src/Test_Tpetra.cc > CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.i

CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.s"
	mpic++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/src/Test_Tpetra.cc -o CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.s

CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o.requires:

.PHONY : CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o.requires

CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o.provides: CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o.requires
	$(MAKE) -f CMakeFiles/tst_trilinos.dir/build.make CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o.provides.build
.PHONY : CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o.provides

CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o.provides.build: CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o


# Object files for target tst_trilinos
tst_trilinos_OBJECTS = \
"CMakeFiles/tst_trilinos.dir/src/main.cc.o" \
"CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o"

# External object files for target tst_trilinos
tst_trilinos_EXTERNAL_OBJECTS =

tst_trilinos: CMakeFiles/tst_trilinos.dir/src/main.cc.o
tst_trilinos: CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o
tst_trilinos: CMakeFiles/tst_trilinos.dir/build.make
tst_trilinos: CMakeFiles/tst_trilinos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable tst_trilinos"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tst_trilinos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tst_trilinos.dir/build: tst_trilinos

.PHONY : CMakeFiles/tst_trilinos.dir/build

CMakeFiles/tst_trilinos.dir/requires: CMakeFiles/tst_trilinos.dir/src/main.cc.o.requires
CMakeFiles/tst_trilinos.dir/requires: CMakeFiles/tst_trilinos.dir/src/Test_Tpetra.cc.o.requires

.PHONY : CMakeFiles/tst_trilinos.dir/requires

CMakeFiles/tst_trilinos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tst_trilinos.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tst_trilinos.dir/clean

CMakeFiles/tst_trilinos.dir/depend:
	cd /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/build /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/build /Users/brbass/Documents/research/code/test_code/linear_algebra/templated_trilinos/build/CMakeFiles/tst_trilinos.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tst_trilinos.dir/depend
