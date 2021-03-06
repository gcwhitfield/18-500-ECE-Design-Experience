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
                    ./libs/serialib/lib/
                    )

# set the names of all of the cpp files into one variable called "NAMES"
set(NAMES ./src/Mode.cpp
          ./src/PlayMode.cpp
          ./src/DrumPeripheral.cpp
          ./src/ColorTextureProgram.cpp
          ./src/Sound.cpp
          ./src/Beatmap.cpp
          ./src/Shader.cpp
          ./src/TextRenderProgram.cpp
          ./src/TextRenderer.cpp
          ./src/MainMenuMode.cpp
          ./src/LoadImage.cpp
          ./src/SongSelectionMode.cpp
          ./src/ScoreScreenMode.cpp
          ./src/FadingScreenTransition.cpp
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

# import serialib
set(SERIALIB_NAMES ./libs/serialib/lib/serialib.cpp)

# import jsoncpp
add_subdirectory(./libs/jsoncpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# import Python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wno-deprecated-declarations -std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

# add the executable
add_executable(RhythmGame libs/glad/src/glad.c ${LIBAUDIODECODER_NAMES} ${NAMES} ${SERIALIB_NAMES} src/main.cpp) # ${LIBAUDIODECODER_NAMES}

# link libraries
target_link_libraries(
	${PROJECT_NAME} 
	glfw ${GLFW_LIBRARIES}
    portaudio
    freetype ${FREETYPE_LIBRARIES}
    harfbuzz
    jsoncpp_static
    ${PYTHON_LIBRARIES}

    )