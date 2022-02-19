cmake_minimum_required(VERSION 3.10)

# set the project name
project(RhythmGame)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -std=c++11")

add_subdirectory(./libs/glfw/)

include_directories(./libs/glfw/include/
                    ./libs/glad/include/
                    ./libs/glm/include/
                    )

# set the names of all of the cpp files into one variable called "NAMES"
set(NAMES ./src/Mode.cpp
          ./src/PlayMode.cpp
          ./src/ColorTextureProgram.cpp
          )


# add the executable
add_executable(RhythmGame libs/glad/src/glad.c ${NAMES} src/main.cpp)

# link GLFW
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})