# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yl10/codes/GCode/LSHBOX-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yl10/codes/GCode/LSHBOX-master/tools

# Include any dependencies generated for this target.
include tools/CMakeFiles/dbqlsh_test.dir/depend.make

# Include the progress variables for this target.
include tools/CMakeFiles/dbqlsh_test.dir/progress.make

# Include the compile flags for this target's objects.
include tools/CMakeFiles/dbqlsh_test.dir/flags.make

tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o: tools/CMakeFiles/dbqlsh_test.dir/flags.make
tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o: dbqlsh_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yl10/codes/GCode/LSHBOX-master/tools/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o"
	cd /home/yl10/codes/GCode/LSHBOX-master/tools/tools && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o -c /home/yl10/codes/GCode/LSHBOX-master/tools/dbqlsh_test.cpp

tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.i"
	cd /home/yl10/codes/GCode/LSHBOX-master/tools/tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yl10/codes/GCode/LSHBOX-master/tools/dbqlsh_test.cpp > CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.i

tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.s"
	cd /home/yl10/codes/GCode/LSHBOX-master/tools/tools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yl10/codes/GCode/LSHBOX-master/tools/dbqlsh_test.cpp -o CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.s

tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o.requires:
.PHONY : tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o.requires

tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o.provides: tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o.requires
	$(MAKE) -f tools/CMakeFiles/dbqlsh_test.dir/build.make tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o.provides.build
.PHONY : tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o.provides

tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o.provides.build: tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o

# Object files for target dbqlsh_test
dbqlsh_test_OBJECTS = \
"CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o"

# External object files for target dbqlsh_test
dbqlsh_test_EXTERNAL_OBJECTS =

bin/linux/dbqlsh_test: tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o
bin/linux/dbqlsh_test: tools/CMakeFiles/dbqlsh_test.dir/build.make
bin/linux/dbqlsh_test: tools/CMakeFiles/dbqlsh_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/linux/dbqlsh_test"
	cd /home/yl10/codes/GCode/LSHBOX-master/tools/tools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dbqlsh_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/CMakeFiles/dbqlsh_test.dir/build: bin/linux/dbqlsh_test
.PHONY : tools/CMakeFiles/dbqlsh_test.dir/build

tools/CMakeFiles/dbqlsh_test.dir/requires: tools/CMakeFiles/dbqlsh_test.dir/dbqlsh_test.cpp.o.requires
.PHONY : tools/CMakeFiles/dbqlsh_test.dir/requires

tools/CMakeFiles/dbqlsh_test.dir/clean:
	cd /home/yl10/codes/GCode/LSHBOX-master/tools/tools && $(CMAKE_COMMAND) -P CMakeFiles/dbqlsh_test.dir/cmake_clean.cmake
.PHONY : tools/CMakeFiles/dbqlsh_test.dir/clean

tools/CMakeFiles/dbqlsh_test.dir/depend:
	cd /home/yl10/codes/GCode/LSHBOX-master/tools && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yl10/codes/GCode/LSHBOX-master /home/yl10/codes/GCode/LSHBOX-master/tools /home/yl10/codes/GCode/LSHBOX-master/tools /home/yl10/codes/GCode/LSHBOX-master/tools/tools /home/yl10/codes/GCode/LSHBOX-master/tools/tools/CMakeFiles/dbqlsh_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/CMakeFiles/dbqlsh_test.dir/depend

