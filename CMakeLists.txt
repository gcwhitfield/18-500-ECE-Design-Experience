cmake_minimum_required(VERSION 3.10)

# set the project name
project(RhythmGame)

include_directories(./libs/glfw/include/
                    ./libs/glad/include/
                    ./libs/glm/include/
                    ./libs/portaudio/include/
		            ./libs/libaudiodecoder/include/
                    ./libs/harfbuzz/include/
                    ./libs/freetype/include/
                    ./libs/jsoncpp/include/
                    )

# set the names of all of the cpp files into one variable called "NAMES"
set(NAMES ./src/Mode.cpp
          ./src/PlayMode.cpp
          ./src/ColorTextureProgram.cpp
          ./src/Sound.cpp
          ./src/Beatmap.cpp
          ./src/Shader.cpp
          ./src/TextRenderProgram.cpp
          ./src/TextRenderer.cpp
          )

# import glfw
add_subdirectory(./libs/glfw/)

# import portaudio
add_subdirectory(./libs/portaudio/ ./build/bin EXCLUDE_FROM_ALL)

# import libaudiodecoder
if (APPLE) # compile for macos
    set (LIBAUDIODECODER_NAMES
                ./libs/libaudiodecoder/src/audiodecoderbase.cpp
                ./libs/libaudiodecoder/src/audiodecodercoreaudio.cpp)
endif (APPLE)
if (WIN32) # compile for windows
    set (LIBAUDIODECODER_NAMES
                ./libs/libaudiodecoder/src/audiodecoderbase.cpp
                ./libs/libaudiodecoder/src/audiodecodermediafoundation.cpp)
endif (WIN32)

# import harfbuzz
add_subdirectory(./libs/harfbuzz)

# import freetype
add_subdirectory(./libs/freetype)

# import serial
# add_subdirectory(./libs/serial) # when this line is uncommented, the program cannot compile because 'catkin' is not installed

# import jsoncpp
add_subdirectory(./libs/jsoncpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wno-deprecated-declarations -std=c++11")

# add the executable
add_executable(RhythmGame libs/glad/src/glad.c ${NAMES} ${LIBAUDIODECODER_NAMES} src/main.cpp)

# link libraries
target_link_libraries(
	${PROJECT_NAME} 
	glfw ${GLFW_LIBRARIES}
    portaudio
    harfbuzz
    freetype ${FREETYPE_LIBRARIES}
    jsoncpp_static
    )