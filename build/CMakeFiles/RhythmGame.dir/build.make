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
include CMakeFiles/RhythmGame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RhythmGame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RhythmGame.dir/flags.make

CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.o: CMakeFiles/RhythmGame.dir/flags.make
CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.o: ../libs/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.o -c "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glad/src/glad.c"

CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glad/src/glad.c" > CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.i

CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/glad/src/glad.c" -o CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.s

CMakeFiles/RhythmGame.dir/src/Mode.cpp.o: CMakeFiles/RhythmGame.dir/flags.make
CMakeFiles/RhythmGame.dir/src/Mode.cpp.o: ../src/Mode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RhythmGame.dir/src/Mode.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RhythmGame.dir/src/Mode.cpp.o -c "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/Mode.cpp"

CMakeFiles/RhythmGame.dir/src/Mode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RhythmGame.dir/src/Mode.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/Mode.cpp" > CMakeFiles/RhythmGame.dir/src/Mode.cpp.i

CMakeFiles/RhythmGame.dir/src/Mode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RhythmGame.dir/src/Mode.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/Mode.cpp" -o CMakeFiles/RhythmGame.dir/src/Mode.cpp.s

CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.o: CMakeFiles/RhythmGame.dir/flags.make
CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.o: ../src/PlayMode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.o -c "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/PlayMode.cpp"

CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/PlayMode.cpp" > CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.i

CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/PlayMode.cpp" -o CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.s

CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.o: CMakeFiles/RhythmGame.dir/flags.make
CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.o: ../src/ColorTextureProgram.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.o -c "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/ColorTextureProgram.cpp"

CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/ColorTextureProgram.cpp" > CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.i

CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/ColorTextureProgram.cpp" -o CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.s

CMakeFiles/RhythmGame.dir/src/main.cpp.o: CMakeFiles/RhythmGame.dir/flags.make
CMakeFiles/RhythmGame.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/RhythmGame.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RhythmGame.dir/src/main.cpp.o -c "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/main.cpp"

CMakeFiles/RhythmGame.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RhythmGame.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/main.cpp" > CMakeFiles/RhythmGame.dir/src/main.cpp.i

CMakeFiles/RhythmGame.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RhythmGame.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/src/main.cpp" -o CMakeFiles/RhythmGame.dir/src/main.cpp.s

# Object files for target RhythmGame
RhythmGame_OBJECTS = \
"CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.o" \
"CMakeFiles/RhythmGame.dir/src/Mode.cpp.o" \
"CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.o" \
"CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.o" \
"CMakeFiles/RhythmGame.dir/src/main.cpp.o"

# External object files for target RhythmGame
RhythmGame_EXTERNAL_OBJECTS =

RhythmGame: CMakeFiles/RhythmGame.dir/libs/glad/src/glad.c.o
RhythmGame: CMakeFiles/RhythmGame.dir/src/Mode.cpp.o
RhythmGame: CMakeFiles/RhythmGame.dir/src/PlayMode.cpp.o
RhythmGame: CMakeFiles/RhythmGame.dir/src/ColorTextureProgram.cpp.o
RhythmGame: CMakeFiles/RhythmGame.dir/src/main.cpp.o
RhythmGame: CMakeFiles/RhythmGame.dir/build.make
RhythmGame: libs/glfw/src/libglfw3.a
RhythmGame: CMakeFiles/RhythmGame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable RhythmGame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RhythmGame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RhythmGame.dir/build: RhythmGame

.PHONY : CMakeFiles/RhythmGame.dir/build

CMakeFiles/RhythmGame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RhythmGame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RhythmGame.dir/clean

CMakeFiles/RhythmGame.dir/depend:
	cd "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/CMakeFiles/RhythmGame.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/RhythmGame.dir/depend
