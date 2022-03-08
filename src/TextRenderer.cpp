#include "TextRenderer.hpp"

TextRenderer::TextRenderer() {
     // initialize font rendering
    {
        // make a map of glyph textures with FreeType
        // 1) Load font with freetype 
		// copied from https://github.com/harfbuzz/harfbuzz-tutorial/blob/master/hello-harfbuzz-freetype.c
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cout << "Could not init FreeType library :(" << std::endl;
            exit(1);
        }

        if (FT_New_Face(ft, font_file.c_str(), 0, &face)) {
            std::cout << "Failed to load font :(" << std::endl;
            exit(1);
        }

        // disable alignment wince what we read from the face (font) is grayscale.
		// this line was copied from https://github.com/ChunanGang/TextBasedGame/blob/main/TextRenderer.cpp
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        FT_Set_Pixel_Sizes(face, 32, 32);
        // 2 load characters into map
        char letter_min = 32;
        char letter_max = 127;
        for (char c = letter_min; c < letter_max; c++) {        
            if (int err = FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "failed to load glyph: " << err << std::endl;
                exit(1);
            }

            // 3) create texture from glyph
            // xcopied from https://github.com/ChunanGang/TextBasedGame/blob/main/TextRenderer.cpp
            GLuint new_tex = 0;
            glGenTextures(1, &new_tex);
            glBindTexture(GL_TEXTURE_2D, new_tex);
            glTexImage2D(
                GL_TEXTURE_2D, 
                0, 
                GL_RED, 
                face->glyph->bitmap.width, 
                face->glyph->bitmap.rows, 
                0, 
                GL_RED, 
                GL_UNSIGNED_BYTE, 
                face->glyph->bitmap.buffer
            );
            Character new_char = {
                new_tex, 
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top)
            };
            characters.insert(std::pair<char, Character>(c, new_char));
        
            // since textures uses a mipmap and we haven't uploaded one, instruct opengl to create one for us
            glGenerateMipmap(GL_TEXTURE_2D);
            // set filtering and wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}

TextRenderer::~TextRenderer() {

}

void TextRenderer::draw(const glm::uvec2 &drawable_size, std::string text, glm::vec2 _loc, glm::vec2 size, glm::u8vec4 color) {
    (void) text;
    (void) _loc;
    (void) pos;
    (void) color;
    (void) size;

    // ---------- render text ----------
    {
        glUseProgram(text_program.program);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        { // use Harfbuzz to shape text
            // create hb-ft font
            hb_font = hb_ft_font_create(face, NULL);

            // create hb_buffer and populate
            hb_buffer = hb_buffer_create();
            if (!hb_buffer_allocation_successful(hb_buffer)) {
                std::cerr << "hb buffer allocation unsuccessfull" << std::endl;
                exit(1);
            }
            hb_buffer_add_utf8(hb_buffer, text.c_str(), -1, 0, -1);
            hb_buffer_guess_segment_properties(hb_buffer);

            // shape it!
            hb_shape(hb_font, hb_buffer, NULL, 0);

            // get glyph information and positions out of the buffer
            unsigned int len = 0;
            info = hb_buffer_get_glyph_infos(hb_buffer, &len);
            if (len <= 0) {
                std::cerr << "hb buffer get glyph infos err" << std::endl;
                exit(1);
            }
            pos = hb_buffer_get_glyph_positions(hb_buffer, &len);
            if (len <= 0) {
                std::cerr << "hb buffer get glyph positions err" << std::endl;
                exit(1);
            }
            
        }
        size_t i = 0;
        float x = 50.0f;
        float y = 50.0f;
        for (char c : text) {
            // first get the hb shaping infos (offset & advance)
            float x_offset = pos[i].x_offset / 64.0f;
            float y_offset = pos[i].y_offset / 64.0f;
            float x_advance = pos[i].x_advance / 64.0f;
            float y_advance = pos[i].y_advance / 64.0f;
            (void) x_offset;
            (void) y_offset;

            // take out the glyph using char
            Character ch = characters[c];
            glm::vec2 loc(x + (x_offset + ch.bearing.x) * size.x, y + (y_offset - (ch.size.y - ch.bearing.y)) * size.y);
            // calculate the actual position
            vertices.clear();
            draw_rectangle(vertices, glm::vec2((loc.x+_loc.x)/drawable_size.x, (loc.y+_loc.y)/drawable_size.y), glm::vec2(size.x * ch.size.x/ drawable_size.x, size.y * ch.size.y / drawable_size.y), glm::u8vec4(0Xff, 0xff, 0xff, 0xff));
            // draw_rectangle(vertices, glm::vec2(0.0, 0.0), size, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, ch.texture_id);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));

            // TODO: figure out why x_advance and y_advance are always 0  
            x += x_advance * size.x * 6 + 80;
            y += y_advance * size.y * 6;
            // std::cout << "x: " << x << ", y: " << y << std::endl;
            // std::cout << "x_offset: " << x_offset << ", y_offset: " << y_offset << std::endl;
            // std::cout << "x_advance: " << x_advance << ", y_advance: " << y_advance << std::endl;
            // std::cout << "i: " << i << std::endl;
            // float a = pos[i].x_offset;

            i++;
            glBindTexture(GL_TEXTURE_2D, 0);

       }
    //    exit(1);
       glUseProgram(0);
    }
}