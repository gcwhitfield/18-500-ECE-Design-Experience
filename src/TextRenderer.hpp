#include "TextRenderProgram.hpp"
#include "Vertex.hpp"

#include <glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <hb.h>
#include <hb-ft.h>

#include <string>
#include <map>
#include <vector>

#ifndef TEXT_RENDERER
#define TEXT_RENDERER

struct TextRenderer {
    TextRenderer();
    ~TextRenderer();

    TextRenderProgram text_program;
    std::string font_file = "art/fonts/Roboto/Roboto-Regular.ttf";

    std::vector<Vertex> vertices;

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

    void draw(const glm::uvec2 &drawable_size, std::string text, glm::vec2 loc, glm::vec2 size, glm::u8vec4 color);
};

#endif