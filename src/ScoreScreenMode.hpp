#include "ColorTextureProgram.hpp"
#include "Mode.hpp"
#include "TextRenderer.hpp"
#include "Vertex.hpp"

#include <glm.hpp>

#include <string>
#include <vector>

#ifndef SCORE_SCREEN_MODE
#define SCORE_SCREEN_MODE

struct ScoreScreenMode : Mode 
{
    ScoreScreenMode();
    ~ScoreScreenMode();
    
    // ---------- score screen info ----------
    int score = 0;
    float song_length = 0;
    size_t song_bpm = 0;
    size_t num_notes_missed = 0;
    size_t num_notes_good = 0;
    size_t num_notes_awesome = 0;
    std::string song_title;
    
    virtual void update(float elapsed) override;

    virtual void handle_key(
        GLFWwindow *window, 
        int key,
        int scancode, 
        int action, 
        int mods) override;

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