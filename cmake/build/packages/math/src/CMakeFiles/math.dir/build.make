# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_COMMAND = /usr/cac/rhel6/cmake/3.1.2/bin/cmake

# The command to remove a file.
RM = /usr/cac/rhel6/cmake/3.1.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/brbass/research/test_code/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brbass/research/test_code/cmake/build

# Include any dependencies generated for this target.
include packages/math/src/CMakeFiles/math.dir/depend.make

# Include the progress variables for this target.
include packages/math/src/CMakeFiles/math.dir/progress.make

# Include the compile flags for this target's objects.
include packages/math/src/CMakeFiles/math.dir/flags.make

packages/math/src/CMakeFiles/math.dir/Add.cc.o: packages/math/src/CMakeFiles/math.dir/flags.make
packages/math/src/CMakeFiles/math.dir/Add.cc.o: ../packages/math/src/Add.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/brbass/research/test_code/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object packages/math/src/CMakeFiles/math.dir/Add.cc.o"
	cd /home/brbass/research/test_code/cmake/build/packages/math/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/math.dir/Add.cc.o -c /home/brbass/research/test_code/cmake/packages/math/src/Add.cc

packages/math/src/CMakeFiles/math.dir/Add.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/math.dir/Add.cc.i"
	cd /home/brbass/research/test_code/cmake/build/packages/math/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/brbass/research/test_code/cmake/packages/math/src/Add.cc > CMakeFiles/math.dir/Add.cc.i

packages/math/src/CMakeFiles/math.dir/Add.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/math.dir/Add.cc.s"
	cd /home/brbass/research/test_code/cmake/build/packages/math/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/brbass/research/test_code/cmake/packages/math/src/Add.cc -o CMakeFiles/math.dir/Add.cc.s

packages/math/src/CMakeFiles/math.dir/Add.cc.o.requires:
.PHONY : packages/math/src/CMakeFiles/math.dir/Add.cc.o.requires

packages/math/src/CMakeFiles/math.dir/Add.cc.o.provides: packages/math/src/CMakeFiles/math.dir/Add.cc.o.requires
	$(MAKE) -f packages/math/src/CMakeFiles/math.dir/build.make packages/math/src/CMakeFiles/math.dir/Add.cc.o.provides.build
.PHONY : packages/math/src/CMakeFiles/math.dir/Add.cc.o.provides

packages/math/src/CMakeFiles/math.dir/Add.cc.o.provides.build: packages/math/src/CMakeFiles/math.dir/Add.cc.o

# Object files for target math
math_OBJECTS = \
"CMakeFiles/math.dir/Add.cc.o"

# External object files for target math
math_EXTERNAL_OBJECTS =

packages/math/src/libmath.a: packages/math/src/CMakeFiles/math.dir/Add.cc.o
packages/math/src/libmath.a: packages/math/src/CMakeFiles/math.dir/build.make
packages/math/src/libmath.a: packages/math/src/CMakeFiles/math.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libmath.a"
	cd /home/brbass/research/test_code/cmake/build/packages/math/src && $(CMAKE_COMMAND) -P CMakeFiles/math.dir/cmake_clean_target.cmake
	cd /home/brbass/research/test_code/cmake/build/packages/math/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/math.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
packages/math/src/CMakeFiles/math.dir/build: packages/math/src/libmath.a
.PHONY : packages/math/src/CMakeFiles/math.dir/build

packages/math/src/CMakeFiles/math.dir/requires: packages/math/src/CMakeFiles/math.dir/Add.cc.o.requires
.PHONY : packages/math/src/CMakeFiles/math.dir/requires

packages/math/src/CMakeFiles/math.dir/clean:
	cd /home/brbass/research/test_code/cmake/build/packages/math/src && $(CMAKE_COMMAND) -P CMakeFiles/math.dir/cmake_clean.cmake
.PHONY : packages/math/src/CMakeFiles/math.dir/clean

packages/math/src/CMakeFiles/math.dir/depend:
	cd /home/brbass/research/test_code/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brbass/research/test_code/cmake /home/brbass/research/test_code/cmake/packages/math/src /home/brbass/research/test_code/cmake/build /home/brbass/research/test_code/cmake/build/packages/math/src /home/brbass/research/test_code/cmake/build/packages/math/src/CMakeFiles/math.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : packages/math/src/CMakeFiles/math.dir/depend
