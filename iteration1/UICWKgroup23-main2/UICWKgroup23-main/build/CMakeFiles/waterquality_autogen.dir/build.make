# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main/build

# Utility rule file for waterquality_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/waterquality_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/waterquality_autogen.dir/progress.make

CMakeFiles/waterquality_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target waterquality"
	/usr/bin/cmake -E cmake_autogen /uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main/build/CMakeFiles/waterquality_autogen.dir/AutogenInfo.json ""

waterquality_autogen: CMakeFiles/waterquality_autogen
waterquality_autogen: CMakeFiles/waterquality_autogen.dir/build.make
.PHONY : waterquality_autogen

# Rule to build all files generated by this target.
CMakeFiles/waterquality_autogen.dir/build: waterquality_autogen
.PHONY : CMakeFiles/waterquality_autogen.dir/build

CMakeFiles/waterquality_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/waterquality_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/waterquality_autogen.dir/clean

CMakeFiles/waterquality_autogen.dir/depend:
	cd /uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main /uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main /uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main/build /uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main/build /uolstore/home/users/sc23tp/Documents/UICWKgroup23-main2/UICWKgroup23-main/build/CMakeFiles/waterquality_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/waterquality_autogen.dir/depend

