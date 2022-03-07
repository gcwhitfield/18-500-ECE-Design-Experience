#include "PlayMode.hpp"

// "stb_image.h" must be included from the .cpp file and not from an .hpp file.
// the following two lines must be place inside of a .cpp file and not a .hpp file. Otherwise, 
// a linker error will occur because STB_IMAGE_IMPLEMENTATION gets defined multiple times. 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

PlayMode::PlayMode() {

    // "create buffer to store vertex information", "create vertex array object...", and 
    // "create solid white texture" sections 
    // were taken from PongMode.cpp from "game 0 base code" of 15-466 at CMU
    // https://github.com/15-466/15-466-f21-base0
    { // create buffer to store vertex information
        glGenBuffers(1, &vertex_buffer_object);
    }

    { // create vertex array object, which tells OpenGL how the vertex buffer object is configured
        glGenVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

        // configure the entries of vertex buffer object
        // 1) position
        // GLintptr position_offset = 0;
        glVertexAttribPointer(
            program.position_vec4, // attribute
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // not normalized
            sizeof(Vertex), // stride
            (GLvoid *)(0) // offset
        );
        glEnableVertexAttribArray(program.position_vec4);
        // 2) color
        // GLintptr color_offset = 4*3;
        glVertexAttribPointer(program.color_vec4, // attribute
            4, // size
            GL_UNSIGNED_BYTE, // type
            GL_TRUE, // normalized
            sizeof(Vertex), // stride
            (GLvoid *)(4 * 3) // offset
        );
        glEnableVertexAttribArray(program.color_vec4);
        // 3) texture coordinates
        // GLintptr tex_coords_offset = 4*3 + 4*1;
        glVertexAttribPointer(program.tex_coords_vec2,
            2, // size
            GL_FLOAT, // type
            GL_FALSE, // normalzied
            sizeof(Vertex), // stride
            (GLvoid *)(4*3 + 4*1)
        );
        glEnableVertexAttribArray(program.tex_coords_vec2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    { // create a solid white texture
        glGenTextures(1, &white_texture);
        glBindTexture(GL_TEXTURE_2D, white_texture);
        glm::uvec2 size(1,1);
        std::vector<glm::u8vec4> data(size.x * size.y, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, 
            GL_RGBA, GL_UNSIGNED_BYTE, data.data());

        // set filtering and wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // since texture uses a mipmap and he have not yet uploaded one, tell opengl to create one
        // for us
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        print_gl_errors();
    }
    { // import x texture. stb_image code from OpenGL programming book by Joey de Vries
        glGenTextures(1, &x_texture);
        glBindTexture(GL_TEXTURE_2D, x_texture);
        int width, height, nr_channels;
        unsigned char *data = stbi_load("images/x.png", &width, &height, &nr_channels, 0);
        if (!data) {
            std::cerr << "could not read x png" << std::endl;
            exit(1);
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
        print_gl_errors();
    }

    { // initialize the test beatmap
        beatmap = new Beatmap();
        size_t test_beatmap_len = 50;
        std::vector<Beatmap::Beat> beats;
        beatmap->beats.reserve(test_beatmap_len);
        float time_between_beats = 1;
        for (size_t i = 0; i < test_beatmap_len; i++) {
            size_t rand_lane = rand() % 4;
            Beatmap::Beat new_beat;
            new_beat.location = (Beatmap::BeatLocation)rand_lane;
            new_beat.time = time_between_beats * i;
            beatmap->beats.push_back(std::make_pair(new_beat, false));
        }
    }

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
            std::cerr << "char: " << c << std::endl;
        
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

    // initialize harfbuzz
    {
        
    }
}

PlayMode::~PlayMode() {

}

void PlayMode::handle_key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    (void) window;
    (void) scancode;
    (void) action;
    (void) mods;

    {   // Detect input from player, grade input, add points to score
        const Input::KeyCode up = Input::KeyCode::W;
        const Input::KeyCode down = Input::KeyCode::S;
        const Input::KeyCode left = Input::KeyCode::A;
        const Input::KeyCode right = Input::KeyCode::D;
        Beatmap::BeatLocation location;

        switch(key)
        {
            case up:
                location = Beatmap::BeatLocation::UP;
                break;
            case down:
                location = Beatmap::BeatLocation::DOWN;
                break;
            case left:
                location = Beatmap::BeatLocation::LEFT;
                break;
            case right:
                location = Beatmap::BeatLocation::RIGHT;
                break;
            default: // the player did not hit a valid key
                return; 
        }

        BeatGrade grade = grade_input(location);
        switch(grade) {
            case BeatGrade::PERFECT:
                score += 100;
                break;
            case BeatGrade::GOOD:
                score += 25;
                break;
            case BeatGrade::MISS:
                score -= 25;
                break;
            default: // do not modify score for BeatGrade::NONE
                break;
        }
    }
    // std::cout << "Key has been pressed: " << key << " : " << scancode << std::endl;
}

PlayMode::BeatGrade PlayMode::grade_input(Beatmap::BeatLocation location) {
    float time = beatmap->process_beat(location);
    if (time < 0.1) { // one tenth of a second
        return BeatGrade::PERFECT;
    } else if (time < 0.5) { // half a second
        return BeatGrade::GOOD;
    } else if (time < 1) { // one second
        return BeatGrade::MISS;
    } else {
        return BeatGrade::NONE;
    }
}

void PlayMode::update(float elapsed) {
    beatmap->update(elapsed);
}

void PlayMode::draw(const glm::uvec2 &drawable_size) {

    // drawing starter code taken from "game 0 base code"
    // https://github.com/15-466/15-466-f21-base0
    vertices.clear();

    beatmap->draw(vertices, drawable_size);

    (void) drawable_size;
    glUseProgram(program.program);
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // send the vertices to the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(vertex_array_object);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, x_texture);

    glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
    print_gl_errors();
    glBindTexture(GL_TEXTURE_2D, 0);

    // ---------- render text ----------
    {
        glUseProgram(text_program.program);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        text_to_display = "llama";
        { // use Harfbuzz to shape text
            // create hb-ft font
            hb_font = hb_ft_font_create(face, NULL);

            // create hb_buffer and populate
            hb_buffer = hb_buffer_create();
            if (!hb_buffer_allocation_successful(hb_buffer)) {
                std::cerr << "hb buffer allocation unsuccessfull" << std::endl;
                exit(1);
            }
            hb_buffer_add_utf8(hb_buffer, text_to_display.c_str(), -1, 0, -1);
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
        for (char c : text_to_display) {
            // first get the hb shaping infos (offset & advance)
            float x_offset = pos[i].x_offset / 64.0f;
            float y_offset = pos[i].y_offset / 64.0f;
            float x_advance = pos[i].x_advance / 64.0f;
            float y_advance = pos[i].y_advance / 64.0f;
            (void) x_offset;
            (void) y_offset;

            // take out the glyph using char
            Character ch = characters[c];
            glm::vec2 scale(2, 2);
            glm::vec2 loc(x + (x_offset + ch.bearing.x) * scale.x, y + (y_offset - (ch.size.y - ch.bearing.y)) * scale.y);
            // calculate the actual position
            vertices.clear();
            draw_rectangle(vertices, glm::vec2(loc.x/drawable_size.x, loc.y/drawable_size.y), glm::vec2(scale.x * ch.size.x/ drawable_size.x, scale.y * ch.size.y / drawable_size.y), glm::u8vec4(0Xff, 0xff, 0xff, 0xff));
            // draw_rectangle(vertices, glm::vec2(0.0, 0.0), scale, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, ch.texture_id);
            glBindVertexArray(vertex_array_object);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            x += x_advance * scale.x * 6 + 80;
            y += y_advance * scale.y * 6;
            std::cout << "x: " << x << ", y: " << y << std::endl;
            std::cout << "x_offset: " << x_offset << ", y_offset: " << y_offset << std::endl;
            std::cout << "x_advance: " << x_advance << ", y_advance: " << y_advance << std::endl;
            std::cout << "i: " << i << std::endl;
            // float a = pos[i].x_offset;
            float a = pos[i].x_offset;
            std::cout << "pos[i].x_offset: " << a << std::endl;
            i++;
            glBindTexture(GL_TEXTURE_2D, 0);

       }
    //    exit(1);
       glUseProgram(0);
    }

    glBindVertexArray(0);    
    glUseProgram(0);
}