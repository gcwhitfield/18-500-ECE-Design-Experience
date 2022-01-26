// glad should be included before other headers (such as GLFW) that require gl.h glad.h will include
// the required gl headers 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mode.hpp"

#include <iostream>

int main()
{
    // this main function was derived from code in chapter 1 of  "Learn OpenGL - Graphics 
    // Programming" by Joey de Vries. https://learnopengl.com/

    // initialize OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    #endif

    // create window
    GLFWwindow *window = glfwCreateWindow(800, 800, "LearningOpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Could not create GL window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Could not initialize GLAD." << std::endl;
        return -1;
    }

    // set the viewport size 
    glm::uvec2 window_size(800, 800);
    glViewport(0, 0, window_size.x, window_size.y);
    auto on_window_resized = [](GLFWwindow *window, int width, int height) {
        (void)window;
        glViewport(0, 0, width, height);
        return;
    };
    glfwSetFramebufferSizeCallback(window, on_window_resized);

    // set callback functions for user input
    glfwSetKeyCallback(window, Mode::handle_key_wrapper);

    // set the current mode to the default mode
    Mode::set_current(std::make_shared<Mode>());


    // render loop
    // based from "game 0" base code's render loop from Computer Game Programming 
    // course at CMU. https://github.com/15-466/15-466-f21-base0/blob/main/main.cpp
    while (Mode::current && !glfwWindowShouldClose(window)) {

        { // call the current mode's update function to deal with elapsed time
            auto current_time = std::chrono::high_resolution_clock::now();
            static auto previous_time = current_time;
            float elapsed = std::chrono::duration<float>(current_time - previous_time).count();
            previous_time = current_time;

            // if frames are taking a long time to process, force the game to lag in order to avoid 
            // "spiral of death"
            elapsed = std::min(0.1f, elapsed);

            Mode::current->update(elapsed);
            if (!Mode::current) break;
        }

        { // draw the current mode to the window
            Mode::current->draw(window_size);
            glfwSwapBuffers(window);
        }

        glfwPollEvents(); // will call input callback functions as needed
    }

    glfwTerminate();
    return 0;
}