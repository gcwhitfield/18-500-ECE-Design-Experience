#include "ColorTextureProgram.hpp"
#include "LoadImage.hpp"
#include "Mode.hpp"
#include "TextRenderer.hpp"
#include "Vertex.hpp"

#include <glm.hpp>
#include <vector>

#ifndef MAIN_MENU_MODE
#define MAIN_MENU_MODE

struct MainMenuMode : Mode 
{
    MainMenuMode();
    ~MainMenuMode();

    virtual void update(float elapsed) override;

    // this function is called when the user presses a key on the keyboard
    virtual void handle_key(
        GLFWwindow *window, 
        int key,
        int scancode, 
        int action, 
        int mods) override;
    
    // this function is called when the user hits the drum
    virtual void handle_drum(std::vector<char> hits) override;

    // ---------- drawing ----------
    TextRenderer text_renderer;
    GLuint tex = -1U;
    ColorTextureProgram program;
    GLuint vertex_buffer_object = -1U;
    GLuint vertex_array_object = -1U;
    GLuint white_texture = -1U;
    GLuint background_texture = -1U;
    GLuint start_texture = -1U;
    GLuint exit_texture = -1U;
    std::vector<Vertex> vertices;

    virtual void draw(glm::uvec2 const &drawable_size) override;
};

#endif