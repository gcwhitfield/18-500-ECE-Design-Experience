#include "Mode.hpp"
#include "ColorTextureProgram.hpp"
#include "Beatmap.hpp"
#include "Vertex.hpp"
#include "Input.hpp"

#include <glm.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <random>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <hb.h>
#include <hb-ft.h>


// PlayMode is where all of the drawing and logic related to gameplay is stored. 
// The scene where the player plays the game is typically referred to as the "play mode"
struct PlayMode : Mode {
    PlayMode();
    ~PlayMode();

    // ---------- gameplay ---------- 
    enum BeatGrade {
        PERFECT, // player hit the note exactly with the beat
        GOOD,  // player hit the note more-or-less with the beat
        MISS, // player did not hit the note on beat at all
        NONE // the player did not hit or miss the beat 
    };
    
    int score = 0;

    // update is called every frame
    virtual void update(float elapsed) override;

    // handle_key gets called whenever the user presses a key which is detected by GLFW
    virtual void handle_key(
        GLFWwindow *window, 
        int key, 
        int scancode, 
        int action, 
        int mods) override;

    Beatmap *beatmap;

    // given a beat location 'location', returns the score to assign to the beat
    BeatGrade grade_input(Beatmap::BeatLocation location);

    // ---------- drawing ----------
    GLuint tex = -1U;
    ColorTextureProgram program;
    GLuint vertex_buffer_object = -1U;
    GLuint vertex_array_object = -1U;
    GLuint white_texture = -1U;
    GLuint x_texture = -1U;

    std::vector<Vertex> vertices;

    // ---------- font ----------
    std::string font_file = "fonts/Syne_Mono/SyneMono-Regular.ttf";

    // Character struct and characters map were derived from an OpenGL tutorial
    // about text rendering
    // https://learnopengl.com/In-Practice/Text-Rendering
    struct Character {
        unsigned int texture_id; // id handle of the glyph texture
        glm::ivec2 size; // size of the glyph
        glm::ivec2 bearing; // offset from baseline to left/top of the glyph
    };

    std::map<char, Character> characters;

    FT_Face face;
    hb_buffer_t *hb_buffer;
    hb_font_t *hb_font;
    hb_glyph_position_t *pos;
    hb_glyph_info_t *info;

    std::string text_to_display;

    // draw is called whenever we want to draw something to the screen
    virtual void draw(glm::uvec2 const &drawable_size) override;
    
    // ---------- debugging -----------
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