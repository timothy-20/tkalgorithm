# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/d/Windows MFC Projects/tkalgorithm"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile"

# Include any dependencies generated for this target.
include lib/CMakeFiles/test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/test.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/test.dir/flags.make

lib/CMakeFiles/test.dir/test/queue_test.cpp.o: lib/CMakeFiles/test.dir/flags.make
lib/CMakeFiles/test.dir/test/queue_test.cpp.o: ../lib/test/queue_test.cpp
lib/CMakeFiles/test.dir/test/queue_test.cpp.o: lib/CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/test.dir/test/queue_test.cpp.o"
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/test.dir/test/queue_test.cpp.o -MF CMakeFiles/test.dir/test/queue_test.cpp.o.d -o CMakeFiles/test.dir/test/queue_test.cpp.o -c "/mnt/d/Windows MFC Projects/tkalgorithm/lib/test/queue_test.cpp"

lib/CMakeFiles/test.dir/test/queue_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/test/queue_test.cpp.i"
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/Windows MFC Projects/tkalgorithm/lib/test/queue_test.cpp" > CMakeFiles/test.dir/test/queue_test.cpp.i

lib/CMakeFiles/test.dir/test/queue_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/test/queue_test.cpp.s"
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/Windows MFC Projects/tkalgorithm/lib/test/queue_test.cpp" -o CMakeFiles/test.dir/test/queue_test.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/test/queue_test.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

lib/test: lib/CMakeFiles/test.dir/test/queue_test.cpp.o
lib/test: lib/CMakeFiles/test.dir/build.make
lib/test: lib/liblibrary.a
lib/test: lib/CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test"
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/test.dir/build: lib/test
.PHONY : lib/CMakeFiles/test.dir/build

lib/CMakeFiles/test.dir/clean:
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib" && $(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/test.dir/clean

lib/CMakeFiles/test.dir/depend:
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/d/Windows MFC Projects/tkalgorithm" "/mnt/d/Windows MFC Projects/tkalgorithm/lib" "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile" "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib" "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib/CMakeFiles/test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : lib/CMakeFiles/test.dir/depend
