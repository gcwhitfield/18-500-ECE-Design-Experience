# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build"

# Utility rule file for ContinuousSubmit.

# Include the progress variables for this target.
include libs/jsoncpp/CMakeFiles/ContinuousSubmit.dir/progress.make

libs/jsoncpp/CMakeFiles/ContinuousSubmit:
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/jsoncpp" && /usr/local/Cellar/cmake/3.18.2/bin/ctest -D ContinuousSubmit

ContinuousSubmit: libs/jsoncpp/CMakeFiles/ContinuousSubmit
ContinuousSubmit: libs/jsoncpp/CMakeFiles/ContinuousSubmit.dir/build.make

.PHONY : ContinuousSubmit

# Rule to build all files generated by this target.
libs/jsoncpp/CMakeFiles/ContinuousSubmit.dir/build: ContinuousSubmit

.PHONY : libs/jsoncpp/CMakeFiles/ContinuousSubmit.dir/build

libs/jsoncpp/CMakeFiles/ContinuousSubmit.dir/clean:
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/jsoncpp" && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousSubmit.dir/cmake_clean.cmake
.PHONY : libs/jsoncpp/CMakeFiles/ContinuousSubmit.dir/clean

libs/jsoncpp/CMakeFiles/ContinuousSubmit.dir/depend:
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/jsoncpp" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/jsoncpp/CMakeFiles/ContinuousSubmit.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : libs/jsoncpp/CMakeFiles/ContinuousSubmit.dir/depend
