#include "PlayMode.hpp"

// "stb_image.h" must be included from the .cpp file and not from an .hpp file.
// the following two lines must be place inside of a .cpp file and not a .hpp file. Otherwise, 
// a linker error will occur because STB_IMAGE_IMPLEMENTATION gets defined multiple times. 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// import sounds
static Sound::Sample splash_sound("./art/sounds/splash.wav");

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
        unsigned char *data = stbi_load("art/images/x.png", &width, &height, &nr_channels, 0);
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
}

PlayMode::~PlayMode() {

}

void PlayMode::handle_key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    (void) window;
    (void) scancode;
    (void) action;
    (void) mods;

    if (action == Input::KeyAction::PRESS) {   
        
        // Detect UP DOWN LEFT RIGHT keyboard input from player, grade input, add points to score
        const Input::KeyCode up = Input::KeyCode::W;
        const Input::KeyCode down = Input::KeyCode::S;
        const Input::KeyCode left = Input::KeyCode::A;
        const Input::KeyCode right = Input::KeyCode::D;
        if (key == up || key == down || key == left || key == right) {
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

        // play splash sound if the 'p' key is pressed 
        {
            if (key == 80) {
                Sound::PlayingSample *new_sample = new Sound::PlayingSample(&splash_sound);
                Sound::play(new_sample);
            }
        }
    }
    // std::cout << "Key has been pressed: " << key << " : " << scancode << " : " << action << " : " << mods << std::endl;
}

PlayMode::BeatGrade PlayMode::grade_input(Beatmap::BeatLocation location) {
    float time = beatmap->process_beat(location);
    if (time < 0) {
        return BeatGrade::NONE;
    } else if (time < 0.1) { // one tenth of a second
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

    // draw text
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBindVertexArray(vertex_array_object);
        text_renderer.draw(drawable_size, "Score: " + std::to_string(score), glm::vec2(-200,500), glm::vec2(2, 2), glm::u8vec4(0xff, 0xff, 0xff, 0xff));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(0);    
    glUseProgram(0);
}