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

# Include any dependencies generated for this target.
include libs/portaudio/tests/CMakeFiles/inputlag.dir/depend.make

# Include the progress variables for this target.
include libs/portaudio/tests/CMakeFiles/inputlag.dir/progress.make

# Include the compile flags for this target's objects.
include libs/portaudio/tests/CMakeFiles/inputlag.dir/flags.make

libs/portaudio/tests/CMakeFiles/inputlag.dir/inputlag.c.o: libs/portaudio/tests/CMakeFiles/inputlag.dir/flags.make
libs/portaudio/tests/CMakeFiles/inputlag.dir/inputlag.c.o: ../libs/glfw/tests/inputlag.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object libs/portaudio/tests/CMakeFiles/inputlag.dir/inputlag.c.o"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/inputlag.dir/inputlag.c.o -c "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/tests/inputlag.c"

libs/portaudio/tests/CMakeFiles/inputlag.dir/inputlag.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/inputlag.c.i"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/tests/inputlag.c" > CMakeFiles/inputlag.dir/inputlag.c.i

libs/portaudio/tests/CMakeFiles/inputlag.dir/inputlag.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/inputlag.c.s"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/tests/inputlag.c" -o CMakeFiles/inputlag.dir/inputlag.c.s

libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: libs/portaudio/tests/CMakeFiles/inputlag.dir/flags.make
libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o: ../libs/glfw/deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/inputlag.dir/__/deps/getopt.c.o -c "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/deps/getopt.c"

libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/getopt.c.i"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/deps/getopt.c" > CMakeFiles/inputlag.dir/__/deps/getopt.c.i

libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/getopt.c.s"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/deps/getopt.c" -o CMakeFiles/inputlag.dir/__/deps/getopt.c.s

libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: libs/portaudio/tests/CMakeFiles/inputlag.dir/flags.make
libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o: ../libs/glfw/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o -c "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/deps/glad_gl.c"

libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/deps/glad_gl.c" > CMakeFiles/inputlag.dir/__/deps/glad_gl.c.i

libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/deps/glad_gl.c" -o CMakeFiles/inputlag.dir/__/deps/glad_gl.c.s

# Object files for target inputlag
inputlag_OBJECTS = \
"CMakeFiles/inputlag.dir/inputlag.c.o" \
"CMakeFiles/inputlag.dir/__/deps/getopt.c.o" \
"CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o"

# External object files for target inputlag
inputlag_EXTERNAL_OBJECTS =

libs/portaudio/tests/inputlag.app/Contents/MacOS/inputlag: libs/portaudio/tests/CMakeFiles/inputlag.dir/inputlag.c.o
libs/portaudio/tests/inputlag.app/Contents/MacOS/inputlag: libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/getopt.c.o
libs/portaudio/tests/inputlag.app/Contents/MacOS/inputlag: libs/portaudio/tests/CMakeFiles/inputlag.dir/__/deps/glad_gl.c.o
libs/portaudio/tests/inputlag.app/Contents/MacOS/inputlag: libs/portaudio/tests/CMakeFiles/inputlag.dir/build.make
libs/portaudio/tests/inputlag.app/Contents/MacOS/inputlag: libs/portaudio/src/libglfw3.a
libs/portaudio/tests/inputlag.app/Contents/MacOS/inputlag: libs/portaudio/tests/CMakeFiles/inputlag.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable inputlag.app/Contents/MacOS/inputlag"
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/inputlag.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/portaudio/tests/CMakeFiles/inputlag.dir/build: libs/portaudio/tests/inputlag.app/Contents/MacOS/inputlag

.PHONY : libs/portaudio/tests/CMakeFiles/inputlag.dir/build

libs/portaudio/tests/CMakeFiles/inputlag.dir/clean:
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" && $(CMAKE_COMMAND) -P CMakeFiles/inputlag.dir/cmake_clean.cmake
.PHONY : libs/portaudio/tests/CMakeFiles/inputlag.dir/clean

libs/portaudio/tests/CMakeFiles/inputlag.dir/depend:
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glfw/tests" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/portaudio/tests/CMakeFiles/inputlag.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : libs/portaudio/tests/CMakeFiles/inputlag.dir/depend

