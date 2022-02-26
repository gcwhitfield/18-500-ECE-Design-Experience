#include "Mode.hpp"
#include "ColorTextureProgram.hpp"
#include "Beatmap.hpp"
#include "Vertex.hpp"
#include "Input.hpp"

#include <glm.hpp>
#include <iostream>
#include <vector>
#include <random>

// PlayMode is where all of the drawing and logic related to gameplay is stored. 
// The scene where the player plays the game is typically referred to as the "play mode"
struct PlayMode : Mode {
    PlayMode();
    ~PlayMode();
    
    GLuint tex = -1U;
    ColorTextureProgram program;
    GLuint vertex_buffer_object = -1U;
    GLuint vertex_array_object = -1U;
    GLuint white_texture = -1U;
    GLuint x_texture = -1U;

    // update is called every frame
    virtual void update(float elapsed) override;

    // handle_key gets called whenever the user presses a key which is detected by GLFW
    virtual void handle_key(
        GLFWwindow *window, 
        int key, 
        int scancode, 
        int action, 
        int mods) override;

    // draw is called whenever we want to draw something to the screen
    virtual void draw(glm::uvec2 const &drawable_size) override;

    std::vector<Vertex> vertices;

    Beatmap beatmap;

    void print_gl_errors()
    {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            switch(err)
            {
                case GL_INVALID_ENUM: {
                    std::cout << "Invalid enum" << std::endl;
                }
                case GL_INVALID_VALUE: {
                    std::cout << "Invalid value" << std::endl;
                }
                case GL_INVALID_OPERATION: {
                    std::cout << "Invalid operation" << std::endl;
                }
                case GL_INVALID_INDEX: {
                    std::cout << "Invalid index" << std::endl;
                }
                case GL_OUT_OF_MEMORY: {
                    std::cout << "Out of memory" << std::endl;
                }
                default: {
                    std::cout << "Unknown error" << std::endl;
                }
            }
        }
    }
};