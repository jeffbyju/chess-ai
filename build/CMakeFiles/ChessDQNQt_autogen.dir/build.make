# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jeffbyju/Documents/chessai

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jeffbyju/Documents/chessai/build

# Utility rule file for ChessDQNQt_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/ChessDQNQt_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ChessDQNQt_autogen.dir/progress.make

CMakeFiles/ChessDQNQt_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/jeffbyju/Documents/chessai/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target ChessDQNQt"
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E cmake_autogen /Users/jeffbyju/Documents/chessai/build/CMakeFiles/ChessDQNQt_autogen.dir/AutogenInfo.json Release

ChessDQNQt_autogen: CMakeFiles/ChessDQNQt_autogen
ChessDQNQt_autogen: CMakeFiles/ChessDQNQt_autogen.dir/build.make
.PHONY : ChessDQNQt_autogen

# Rule to build all files generated by this target.
CMakeFiles/ChessDQNQt_autogen.dir/build: ChessDQNQt_autogen
.PHONY : CMakeFiles/ChessDQNQt_autogen.dir/build

CMakeFiles/ChessDQNQt_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ChessDQNQt_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ChessDQNQt_autogen.dir/clean

CMakeFiles/ChessDQNQt_autogen.dir/depend:
	cd /Users/jeffbyju/Documents/chessai/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jeffbyju/Documents/chessai /Users/jeffbyju/Documents/chessai /Users/jeffbyju/Documents/chessai/build /Users/jeffbyju/Documents/chessai/build /Users/jeffbyju/Documents/chessai/build/CMakeFiles/ChessDQNQt_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ChessDQNQt_autogen.dir/depend

