#include "Mode.hpp"
#include "ColorTextureProgram.hpp"
#include <glm.hpp>
#include <iostream>
#include <vector>

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
    GLuint llama_texture = -1U;

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

    // 'Vertex' stores the information that we give to OpenGL in the vertex buffer
    struct Vertex {
        Vertex(glm::vec3 pos, glm::u8vec4 col, glm::vec2 tex) : position(pos), color(col), tex_coord(tex) {
            position = pos;
            color = col;
            tex_coord = tex;
        }
        ~Vertex() {};
        glm::vec3 position;
        glm::u8vec4 color;
        glm::vec2 tex_coord;
    };

    std::vector<Vertex> vertices;

    // inline helper functions for drawing shapes. The triangles are being counter clockwise.
    // draw_rectangle copied from NEST framework 
    // https://github.com/gcwhitfield/Game-Programming-f21-base6/blob/main/NEST.md
    inline void draw_rectangle (std::vector<Vertex> &verts, glm::vec2 const &center, glm::vec2 const &radius, glm::u8vec4 const &color) {
        verts.emplace_back(Vertex(glm::vec3(center.x-radius.x, center.y-radius.y, 0.0f), color, glm::vec2(0.0f, 1.0f))); // top left
        verts.emplace_back(Vertex(glm::vec3(center.x+radius.x, center.y-radius.y, 0.0f), color, glm::vec2(1.0f, 1.0f))); // top right
        verts.emplace_back(Vertex(glm::vec3(center.x+radius.x, center.y+radius.y, 0.0f), color, glm::vec2(1.0f, 0.0f))); // bottom right

        verts.emplace_back(Vertex(glm::vec3(center.x-radius.x, center.y-radius.y, 0.0f), color, glm::vec2(0.0f, 1.0f))); // top left
        verts.emplace_back(Vertex(glm::vec3(center.x+radius.x, center.y+radius.y, 0.0f), color, glm::vec2(1.0f, 0.0f))); // bottom right
        verts.emplace_back(Vertex(glm::vec3(center.x-radius.x, center.y+radius.y, 0.0f), color, glm::vec2(0.0f, 0.0f))); // bottom left
    };

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