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
include lib/src/CMakeFiles/tkmodules.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/src/CMakeFiles/tkmodules.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/src/CMakeFiles/tkmodules.dir/progress.make

# Include the compile flags for this target's objects.
include lib/src/CMakeFiles/tkmodules.dir/flags.make

lib/src/CMakeFiles/tkmodules.dir/queue.cpp.o: lib/src/CMakeFiles/tkmodules.dir/flags.make
lib/src/CMakeFiles/tkmodules.dir/queue.cpp.o: ../lib/src/queue.cpp
lib/src/CMakeFiles/tkmodules.dir/queue.cpp.o: lib/src/CMakeFiles/tkmodules.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/src/CMakeFiles/tkmodules.dir/queue.cpp.o"
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/src/CMakeFiles/tkmodules.dir/queue.cpp.o -MF CMakeFiles/tkmodules.dir/queue.cpp.o.d -o CMakeFiles/tkmodules.dir/queue.cpp.o -c "/mnt/d/Windows MFC Projects/tkalgorithm/lib/src/queue.cpp"

lib/src/CMakeFiles/tkmodules.dir/queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tkmodules.dir/queue.cpp.i"
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/Windows MFC Projects/tkalgorithm/lib/src/queue.cpp" > CMakeFiles/tkmodules.dir/queue.cpp.i

lib/src/CMakeFiles/tkmodules.dir/queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tkmodules.dir/queue.cpp.s"
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/Windows MFC Projects/tkalgorithm/lib/src/queue.cpp" -o CMakeFiles/tkmodules.dir/queue.cpp.s

# Object files for target tkmodules
tkmodules_OBJECTS = \
"CMakeFiles/tkmodules.dir/queue.cpp.o"

# External object files for target tkmodules
tkmodules_EXTERNAL_OBJECTS =

lib/src/libtkmodules.a: lib/src/CMakeFiles/tkmodules.dir/queue.cpp.o
lib/src/libtkmodules.a: lib/src/CMakeFiles/tkmodules.dir/build.make
lib/src/libtkmodules.a: lib/src/CMakeFiles/tkmodules.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtkmodules.a"
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib/src" && $(CMAKE_COMMAND) -P CMakeFiles/tkmodules.dir/cmake_clean_target.cmake
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tkmodules.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/src/CMakeFiles/tkmodules.dir/build: lib/src/libtkmodules.a
.PHONY : lib/src/CMakeFiles/tkmodules.dir/build

lib/src/CMakeFiles/tkmodules.dir/clean:
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib/src" && $(CMAKE_COMMAND) -P CMakeFiles/tkmodules.dir/cmake_clean.cmake
.PHONY : lib/src/CMakeFiles/tkmodules.dir/clean

lib/src/CMakeFiles/tkmodules.dir/depend:
	cd "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/d/Windows MFC Projects/tkalgorithm" "/mnt/d/Windows MFC Projects/tkalgorithm/lib/src" "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile" "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib/src" "/mnt/d/Windows MFC Projects/tkalgorithm/cmake-build-wsl_profile/lib/src/CMakeFiles/tkmodules.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : lib/src/CMakeFiles/tkmodules.dir/depend
