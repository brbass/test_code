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
CMAKE_SOURCE_DIR = /home/brbass/research/test_code/operator/aztec

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brbass/research/test_code/operator/aztec/build

# Include any dependencies generated for this target.
include CMakeFiles/aztec_oper.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/aztec_oper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/aztec_oper.dir/flags.make

CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o: CMakeFiles/aztec_oper.dir/flags.make
CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o: ../src/Vector_Operator.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/brbass/research/test_code/operator/aztec/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o"
	mpic++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o -c /home/brbass/research/test_code/operator/aztec/src/Vector_Operator.cc

CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.i"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/brbass/research/test_code/operator/aztec/src/Vector_Operator.cc > CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.i

CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.s"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/brbass/research/test_code/operator/aztec/src/Vector_Operator.cc -o CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.s

CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o.requires:
.PHONY : CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o.requires

CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o.provides: CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o.requires
	$(MAKE) -f CMakeFiles/aztec_oper.dir/build.make CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o.provides.build
.PHONY : CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o.provides

CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o.provides.build: CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o

CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o: CMakeFiles/aztec_oper.dir/flags.make
CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o: ../src/Epetra_Operator_Interface.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/brbass/research/test_code/operator/aztec/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o"
	mpic++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o -c /home/brbass/research/test_code/operator/aztec/src/Epetra_Operator_Interface.cc

CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.i"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/brbass/research/test_code/operator/aztec/src/Epetra_Operator_Interface.cc > CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.i

CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.s"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/brbass/research/test_code/operator/aztec/src/Epetra_Operator_Interface.cc -o CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.s

CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o.requires:
.PHONY : CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o.requires

CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o.provides: CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o.requires
	$(MAKE) -f CMakeFiles/aztec_oper.dir/build.make CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o.provides.build
.PHONY : CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o.provides

CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o.provides.build: CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o

CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o: CMakeFiles/aztec_oper.dir/flags.make
CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o: ../src/Identity_Operator.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/brbass/research/test_code/operator/aztec/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o"
	mpic++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o -c /home/brbass/research/test_code/operator/aztec/src/Identity_Operator.cc

CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.i"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/brbass/research/test_code/operator/aztec/src/Identity_Operator.cc > CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.i

CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.s"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/brbass/research/test_code/operator/aztec/src/Identity_Operator.cc -o CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.s

CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o.requires:
.PHONY : CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o.requires

CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o.provides: CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o.requires
	$(MAKE) -f CMakeFiles/aztec_oper.dir/build.make CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o.provides.build
.PHONY : CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o.provides

CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o.provides.build: CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o

CMakeFiles/aztec_oper.dir/src/Check.cc.o: CMakeFiles/aztec_oper.dir/flags.make
CMakeFiles/aztec_oper.dir/src/Check.cc.o: ../src/Check.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/brbass/research/test_code/operator/aztec/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/aztec_oper.dir/src/Check.cc.o"
	mpic++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aztec_oper.dir/src/Check.cc.o -c /home/brbass/research/test_code/operator/aztec/src/Check.cc

CMakeFiles/aztec_oper.dir/src/Check.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aztec_oper.dir/src/Check.cc.i"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/brbass/research/test_code/operator/aztec/src/Check.cc > CMakeFiles/aztec_oper.dir/src/Check.cc.i

CMakeFiles/aztec_oper.dir/src/Check.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aztec_oper.dir/src/Check.cc.s"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/brbass/research/test_code/operator/aztec/src/Check.cc -o CMakeFiles/aztec_oper.dir/src/Check.cc.s

CMakeFiles/aztec_oper.dir/src/Check.cc.o.requires:
.PHONY : CMakeFiles/aztec_oper.dir/src/Check.cc.o.requires

CMakeFiles/aztec_oper.dir/src/Check.cc.o.provides: CMakeFiles/aztec_oper.dir/src/Check.cc.o.requires
	$(MAKE) -f CMakeFiles/aztec_oper.dir/build.make CMakeFiles/aztec_oper.dir/src/Check.cc.o.provides.build
.PHONY : CMakeFiles/aztec_oper.dir/src/Check.cc.o.provides

CMakeFiles/aztec_oper.dir/src/Check.cc.o.provides.build: CMakeFiles/aztec_oper.dir/src/Check.cc.o

CMakeFiles/aztec_oper.dir/src/main.cc.o: CMakeFiles/aztec_oper.dir/flags.make
CMakeFiles/aztec_oper.dir/src/main.cc.o: ../src/main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/brbass/research/test_code/operator/aztec/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/aztec_oper.dir/src/main.cc.o"
	mpic++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/aztec_oper.dir/src/main.cc.o -c /home/brbass/research/test_code/operator/aztec/src/main.cc

CMakeFiles/aztec_oper.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aztec_oper.dir/src/main.cc.i"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/brbass/research/test_code/operator/aztec/src/main.cc > CMakeFiles/aztec_oper.dir/src/main.cc.i

CMakeFiles/aztec_oper.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aztec_oper.dir/src/main.cc.s"
	mpic++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/brbass/research/test_code/operator/aztec/src/main.cc -o CMakeFiles/aztec_oper.dir/src/main.cc.s

CMakeFiles/aztec_oper.dir/src/main.cc.o.requires:
.PHONY : CMakeFiles/aztec_oper.dir/src/main.cc.o.requires

CMakeFiles/aztec_oper.dir/src/main.cc.o.provides: CMakeFiles/aztec_oper.dir/src/main.cc.o.requires
	$(MAKE) -f CMakeFiles/aztec_oper.dir/build.make CMakeFiles/aztec_oper.dir/src/main.cc.o.provides.build
.PHONY : CMakeFiles/aztec_oper.dir/src/main.cc.o.provides

CMakeFiles/aztec_oper.dir/src/main.cc.o.provides.build: CMakeFiles/aztec_oper.dir/src/main.cc.o

# Object files for target aztec_oper
aztec_oper_OBJECTS = \
"CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o" \
"CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o" \
"CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o" \
"CMakeFiles/aztec_oper.dir/src/Check.cc.o" \
"CMakeFiles/aztec_oper.dir/src/main.cc.o"

# External object files for target aztec_oper
aztec_oper_EXTERNAL_OBJECTS =

aztec_oper: CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o
aztec_oper: CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o
aztec_oper: CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o
aztec_oper: CMakeFiles/aztec_oper.dir/src/Check.cc.o
aztec_oper: CMakeFiles/aztec_oper.dir/src/main.cc.o
aztec_oper: CMakeFiles/aztec_oper.dir/build.make
aztec_oper: CMakeFiles/aztec_oper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable aztec_oper"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aztec_oper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/aztec_oper.dir/build: aztec_oper
.PHONY : CMakeFiles/aztec_oper.dir/build

CMakeFiles/aztec_oper.dir/requires: CMakeFiles/aztec_oper.dir/src/Vector_Operator.cc.o.requires
CMakeFiles/aztec_oper.dir/requires: CMakeFiles/aztec_oper.dir/src/Epetra_Operator_Interface.cc.o.requires
CMakeFiles/aztec_oper.dir/requires: CMakeFiles/aztec_oper.dir/src/Identity_Operator.cc.o.requires
CMakeFiles/aztec_oper.dir/requires: CMakeFiles/aztec_oper.dir/src/Check.cc.o.requires
CMakeFiles/aztec_oper.dir/requires: CMakeFiles/aztec_oper.dir/src/main.cc.o.requires
.PHONY : CMakeFiles/aztec_oper.dir/requires

CMakeFiles/aztec_oper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/aztec_oper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/aztec_oper.dir/clean

CMakeFiles/aztec_oper.dir/depend:
	cd /home/brbass/research/test_code/operator/aztec/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brbass/research/test_code/operator/aztec /home/brbass/research/test_code/operator/aztec /home/brbass/research/test_code/operator/aztec/build /home/brbass/research/test_code/operator/aztec/build /home/brbass/research/test_code/operator/aztec/build/CMakeFiles/aztec_oper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/aztec_oper.dir/depend

