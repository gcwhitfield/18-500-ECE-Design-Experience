#include "PlayMode.hpp"

// "stb_image.h" must be included from the .cpp file and not from an .hpp file.
// the following two lines must be place inside of a .cpp file and not a .hpp file. Otherwise, 
// a linker error will occur because STB_IMAGE_IMPLEMENTATION gets defined multiple times. 
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

// import images
static std::string background_img("./art/images/background.png");
static std::string note_img("./art/images/note.png");
static std::string healthbar_background_img("./art/images/health bar background.png");
static std::string healthbar_top_img("./art/images/health bar top.png");

PlayMode::PlayMode(std::string song_path) : 
    song_path(song_path), music_file(song_path + "/song.mp3"), beatmap_file(song_path + "/beatmap.json"){

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
    
    { // import textures

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

        { // import note texture. stb_image code from OpenGL programming book by Joey de Vries
            LoadImage::load_img(&notes_texture, note_img);
            print_gl_errors();
        }

        { // import background texture
            LoadImage::load_img(&background_texture, background_img);
            print_gl_errors();
        }

        { // import health bar textures
            LoadImage::load_img(&healthbar_background_texture, healthbar_background_img);
            LoadImage::load_img(&healthbar_top_texture, healthbar_top_img);
            print_gl_errors();
        }
    
    }

    {   // initialize test beatmap from JSON 
        Beatmap *b = new Beatmap(beatmap_file);
        beatmap = b;
    }

    { // play music
        music = new Sound::PlayingSample(&music_file);
        Sound::play(music);
    } 

    { // initialize drums
      drums = new DrumPeripheral();
    }

    { // initialize beat grade display
        beat_grade_display.lifetime = -1;
    }
    
    { // initialize the fading screen transition
        fading_screen_transition.play(
            FadingScreenTransition::ScreenTransitionAnimType::OPEN,
            2.0f,
            glm::u8vec4(0x00, 0x00, 0x00, 0x00
        ));
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

            switch(key) {
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

    }
    // std::cout << "Key has been pressed: " << key << " : " << scancode << " : " << action << " : " << mods << std::endl;
}

void PlayMode::handle_drum(std::vector<char> hits) {
    (void) hits;
    // std::cout << (int)hits[0] << " : " << (int)hits[1] << " : " << (int)hits[2] << " : " << (int)hits[3] << std::endl;
    if (hits[3] == DrumPeripheral::HitInfo::PRESS) {
        std::cout << "pressed left" << std::endl;
        BeatGrade grade = grade_input(Beatmap::BeatLocation::RIGHT);
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
    if (hits[2] == DrumPeripheral::HitInfo::PRESS) {
        std::cout << "pressed up" << std::endl;
        BeatGrade grade = grade_input(Beatmap::BeatLocation::UP);
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
    if (hits[1] == DrumPeripheral::HitInfo::PRESS) {
        std::cout << "pressed down" << std::endl;
        BeatGrade grade = grade_input(Beatmap::BeatLocation::DOWN);
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
    if (hits[0] == DrumPeripheral::HitInfo::PRESS) {
        std::cout << "pressed right" << std::endl;
        BeatGrade grade = grade_input(Beatmap::BeatLocation::LEFT);
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
}

PlayMode::BeatGrade PlayMode::grade_input(Beatmap::BeatLocation location) {
    // display the beat grade display
    float time = beatmap->process_beat(location);
    if (time < 0) {
        return BeatGrade::NONE;
    } else if (time < 0.1) { // one tenth of a second
        beat_grade_display.lifetime = 0.5f;
        beat_grade_display.grade = PERFECT;
        return BeatGrade::PERFECT;
    } else if (time < 0.5) { // half a second
        beat_grade_display.lifetime = 0.5f;
        beat_grade_display.grade = GOOD;
        return BeatGrade::GOOD;
    } else if (time < 1) { // one second
        beat_grade_display.lifetime = 0.5f;
        beat_grade_display.grade = MISS;
        return BeatGrade::MISS;
    } else {
        return BeatGrade::NONE;
    }
}

void PlayMode::level_finished() {
    music->stop = true;
    Mode::set_current(std::make_shared<ScoreScreenMode>());
}

void PlayMode::update(float elapsed) {
    drums->update(elapsed);
    fading_screen_transition.update(elapsed);

    beatmap->update(elapsed);
    if (beatmap->beats.size() == 0) {
        level_finished();
    }

    if (beat_grade_display.lifetime > 0) {
        beat_grade_display.lifetime -= elapsed;
    }

}

void PlayMode::draw(const glm::uvec2 &drawable_size) {
    (void) drawable_size;

    // drawing starter code taken from "game 0 base code"
    // https://github.com/15-466/15-466-f21-base0

    glUseProgram(program.program);
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    { // draw the background
        vertices.clear();
        draw_rectangle(vertices, glm::vec2(0.0, 0.0), glm::vec2(1, 1), glm::u8vec4(0xff, 0xff, 0xff, 0xff));

        // send the vertices to the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindVertexArray(vertex_array_object);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, background_texture);

        // run the OpenGL pipeline
        glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
        print_gl_errors();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    { // draw beatmap
        vertices.clear();
        beatmap->draw(vertices, drawable_size);

        // send the vertices to the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindVertexArray(vertex_array_object);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, notes_texture);

        glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
        print_gl_errors();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // draw text
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBindVertexArray(vertex_array_object);
        text_renderer.draw(drawable_size, "Score: " + std::to_string(score), glm::vec2(200,700), glm::vec2(2, 2), glm::u8vec4(0xff, 0xff, 0xff, 0xff));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glUseProgram(program.program);

    { // draw health bar
        vertices.clear();
        glm::vec2 health_bar_loc(-0.6, 0.8);
        glm::vec2 health_bar_size(0.4, 0.1);
        draw_rectangle(vertices, health_bar_loc, health_bar_size, glm::u8vec4(0xff, 0xff, 0xff, 0xff));

        // send the vertices to the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindVertexArray(vertex_array_object);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, healthbar_background_texture);

        // run the OpenGL pipeline
        glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
        print_gl_errors();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    { // draw beat grade display
        if (beat_grade_display.lifetime > 0) {
            {
                std::string text;
                switch (beat_grade_display.grade) {
                    case BeatGrade::PERFECT:
                        text = "PERFECT";
                        break;
                    case BeatGrade::GOOD:
                        text = "GOOD";
                        break;
                    case BeatGrade::MISS:
                        text = "MISS";
                        break;
                    case BeatGrade::NONE:
                        text = "NONE";
                        break;
                }
                glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
                glBindVertexArray(vertex_array_object);
                text_renderer.draw(drawable_size, text, glm::vec2(-600,300), glm::vec2(2, 2), glm::u8vec4(0xff, 0xff, 0xff, 0xff));
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glUseProgram(program.program);
            }
        }
    }

    { // draw the screen transition
        if (fading_screen_transition.is_active()) {
            fading_screen_transition.draw(drawable_size);

            // send the vertices to the vertex buffer
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
            glBufferData(
                GL_ARRAY_BUFFER, 
                fading_screen_transition.vertices.size() * sizeof(fading_screen_transition.vertices[0]), 
                fading_screen_transition.vertices.data(),
                GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            glBindVertexArray(vertex_array_object);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, white_texture);

            glDrawArrays(GL_TRIANGLES, 0, GLsizei(fading_screen_transition.vertices.size()));
            print_gl_errors();
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    glBindVertexArray(0);    
    glUseProgram(0);
}