cmake_minimum_required(VERSION 3.10)

# set the project name
project(RhythmGame)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wno-deprecated-declarations -std=c++11")



add_subdirectory(./libs/glfw/)

add_subdirectory(./libs/portaudio/ ./build/bin EXCLUDE_FROM_ALL)

include_directories(./libs/glfw/include/
                    ./libs/glad/include/
                    ./libs/glm/include/
                    ./libs/portaudio/include/
		            ./libs/libaudiodecoder/include/
                    )

# set the names of all of the cpp files into one variable called "NAMES"
set(NAMES ./src/Mode.cpp
          ./src/PlayMode.cpp
          ./src/ColorTextureProgram.cpp
          ./src/Sound.cpp
          ./src/Beatmap.cpp
          )

# file(GLOB_RECURSE LIBAUDIODECODER_NAMES ./libs/libaudiodecoder/src/**.cpp)


# add the executable
add_executable(RhythmGame libs/glad/src/glad.c ${NAMES} ${LIBAUDIODECODER_NAMES} src/main.cpp)

# link libraries
target_link_libraries(
	${PROJECT_NAME} 
	glfw ${GLFW_LIBRARIES}
    	portaudio
    )