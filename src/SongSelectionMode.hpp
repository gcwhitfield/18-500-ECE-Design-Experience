#include "ColorTextureProgram.hpp"
#include "Mode.hpp"
#include "TextRenderer.hpp"
#include "Vertex.hpp"

#include <glm.hpp>
#include <vector>

#ifndef SONG_SELECTION_MODE
#define SONG_SELECTION_MODE

struct SongSelectionMode : Mode 
{
    SongSelectionMode();
    ~SongSelectionMode();

    virtual void update(float elapsed) override;

    virtual void handle_key(
        GLFWwindow *window, 
        int key,
        int scancode, 
        int action, 
        int mods) override;

    // this function is called when the user hits the drum
    virtual void handle_drum(std::vector<char> hits) override;

    // ---------- drawing ----------
    std::vector<Vertex> vertices;
    TextRenderer text_renderer;
    GLuint tex = -1U;
    ColorTextureProgram program;
    GLuint vertex_buffer_object = -1U;
    GLuint vertex_array_object = -1U;
    GLuint white_texture = -1U;
        
    virtual void draw(glm::uvec2 const &drawable_size) override;
};

#endif