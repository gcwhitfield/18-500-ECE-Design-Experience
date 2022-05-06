#include "SongSelectionMode.hpp"

// "stb_image.h" must be included from the .cpp file and not from an .hpp file.
// the following two lines must be place inside of a .cpp file and not a .hpp file. Otherwise, 
// a linker error will occur because STB_IMAGE_IMPLEMENTATION gets defined multiple times. 
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

// import sounds
static Sound::Sample song_selection_swoosh("./art/sounds/song selection swoosh.mp3");
static Sound::Sample bloop_cmaj("./art/sounds/bloop_cmaj911_ascending.mp3");

// image file paths
static std::string song_selection_box_img("./art/images/song selection box.png");
static std::string background_img("./art/images/background.png");

// song info display parameters
static float spacing_vert = 0.25; // vertical spacing between each song info
static float spacing_horz = 0.0; // the horz offset of each song info

SongSelectionMode::SongSelectionMode() {
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

    { // load song selection background boc
        LoadImage::load_img(&song_selection_box_texture, song_selection_box_img);
        print_gl_errors();
    }

    { // 1) obtain a vector of all of the files in the songs directory (song_files)
      // 2) upload into songs vector (vector of song data)
        song_files = Directory::list_dir("songs");
        for (size_t i = 0; i < songs.size(); i++) {
            std::cout << i << ": " << song_files[i] << std::endl;
        }
        songs.clear();
        songs.resize(song_files.size());
        for (size_t i = 0; i < songs.size(); i++) {
            SongInfo info;
            info.curr_pos = glm::vec2(0,0);
            info.desired_pos = glm::vec2(0,0);
            songs[i] = info;
        }
        set_song_positions();
    }

    { // initialize state
        state = SongSelectionState::SELECTING;
        fading_screen_transition.play(
            FadingScreenTransition::ScreenTransitionAnimType::OPEN,
            4.0f,
            glm::u8vec4(0xff, 0xff, 0xff, 0xff)
        );
    }

    { // import background texture
        LoadImage::load_img(&background_texture, background_img);
        print_gl_errors();
    }

    { // initialize drums
        drums = new DrumPeripheral();
    }
}

SongSelectionMode::~SongSelectionMode() {

}

void SongSelectionMode::set_song_positions() {
    for (int j = 0; j < songs.size(); j++) {
        size_t i = (j + curr_selected) % songs.size();
        int dist_from_selected = (int)curr_selected - i;
        glm::vec2 pos(0.3 + std::abs(dist_from_selected)*spacing_horz, 0.5f + spacing_vert*dist_from_selected);
        songs[i].desired_pos = pos;
    }
}

void SongSelectionMode::change_selection(int dir) {
    if (dir < 0) {
        // decrement selection
        if (curr_selected == 0) {
            curr_selected = songs.size() - 1;
        } else {
            curr_selected --;
        }
    } else {
        // incremenet selection
        curr_selected ++;
        if (curr_selected >= songs.size()) {
            curr_selected = 0;
        }
    }
    Sound::PlayingSample *bloop = new Sound::PlayingSample(&song_selection_swoosh);
    Sound::play(bloop);


}

void SongSelectionMode::handle_key(GLFWwindow *window, int key, int scancode, int actions, int mods) {
    (void) window;
    (void) key;
    (void) scancode;
    (void) actions;
    (void) mods;

    if (state == SongSelectionState::SELECTING) {
        if (actions == Input::KeyAction::PRESS) {
            if (key == Input::KeyCode::A) {
                change_selection(1);
            } else if (key == Input::KeyCode::D) {
                change_selection(-1);
            } else if (key == Input::KeyCode::ENTER) {
                // go to PlayMode when the player presses Enter
                fading_screen_transition.play(
                    FadingScreenTransition::ScreenTransitionAnimType::CLOSE,
                    2.0f, 
                    glm::u8vec4(0x00, 0x00, 0x00, 0x00)
                );
                Sound::PlayingSample *confirmed_noise = new Sound::PlayingSample(&bloop_cmaj);
                Sound::play(confirmed_noise);
                state = SongSelectionState::CONFIRMED;
            }
        }
    }

    set_song_positions();
}

void SongSelectionMode::handle_drum(std::vector<char> hits) {
    if (state == SELECTING) {
        if (hits[3] == DrumPeripheral::HitInfo::PRESS) { // right drum
            change_selection(1);
        }
        if (hits[2] == DrumPeripheral::HitInfo::PRESS) { // right middle drum
            // go to PlayMode when the player presses the right middle drum
            fading_screen_transition.play(
                FadingScreenTransition::ScreenTransitionAnimType::CLOSE,
                2.0f, 
                glm::u8vec4(0x00, 0x00, 0x00, 0x00)
            );
            Sound::PlayingSample *confirmed_noise = new Sound::PlayingSample(&bloop_cmaj);
            Sound::play(confirmed_noise);
            state = SongSelectionState::CONFIRMED;
        }
        if (hits[1] == DrumPeripheral::HitInfo::PRESS) { // left middle drum
        }
        if (hits[0] == DrumPeripheral::HitInfo::PRESS) { // left drum
            change_selection(-1);
        }
        set_song_positions();

    }
}

void SongSelectionMode::update(float elapsed) {
    drums->update(elapsed);

    { // smoothly interpolate the positions of the song info displays
        for (size_t i = 0; i < songs.size(); i++) {
            float EPS = 0.01;
            float t = 10.0f * elapsed; // make this number bigger to make the animation faster
            float new_pos_x = songs[i].curr_pos.x*(1.0f-t) + songs[i].desired_pos.x*t;
            float new_pos_y = songs[i].curr_pos.y*(1.0f-t) + songs[i].desired_pos.y*t;
            
            // snap song infos into pos if they are very close to desired pos
            if (std::abs(songs[i].desired_pos.x - new_pos_x) + std::abs(songs[i].desired_pos.y - new_pos_y) < EPS) {
                songs[i].curr_pos = songs[i].desired_pos;
            } else { // otherwise, smoothly interpolate to the desired pos
                songs[i].curr_pos.x = new_pos_x;
                songs[i].curr_pos.y = new_pos_y;
            }
        }
    }

    fading_screen_transition.update(elapsed);
    if (state == SongSelectionState::CONFIRMED) {
        if (fading_screen_transition.is_finished()) { 
            { // executed when the mode is ready to transition to the next mode
                Mode::set_current(std::make_shared<PlayMode>("./songs/" + song_files[curr_selected]));
            }
        }
    }
}

void SongSelectionMode::draw(glm::uvec2 const &drawable_size) {
    // drawing starter code taken from "game 0 base code"
    // https://github.com/15-466/15-466-f21-base0
    vertices.clear();

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
    glBindTexture(GL_TEXTURE_2D, white_texture);

    glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
    print_gl_errors();
    glBindTexture(GL_TEXTURE_2D, 0);

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

    { // draw the list of songs in 'songs' directory
        for (size_t i = 0; i < songs.size(); i++) {
            vertices.clear();
            glm::u8vec4 selected_col(0xaa, 0xaa, 0xaa, 0xff);
            glm::u8vec4 unselected_col(0xff, 0xff, 0xff, 0xff);
            glm::u8vec4 col = i == curr_selected ? selected_col : unselected_col;
            draw_rectangle(vertices, songs[i].curr_pos, glm::vec2(0.4, 0.1), col);
        
            // draw the background 
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(vertex_array_object);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, song_selection_box_texture);
            glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
            glBindTexture(GL_TEXTURE_2D, 0);
            print_gl_errors();

            // draw text
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
            glBindVertexArray(vertex_array_object);
            float text_offset = -0.32;
            glm::vec2 text_size(2, 2);
            text_renderer.draw(drawable_size, song_files[i], glm::vec2((songs[i].curr_pos.x + text_offset) * drawable_size.x, songs[i].curr_pos.y * drawable_size.y), text_size, glm::u8vec4(0x00, 0x00, 0x00, 0xff));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glUseProgram(program.program);
        }
    }
    { // draw title text
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBindVertexArray(vertex_array_object);
        text_renderer.draw(drawable_size, "Select a song", glm::vec2(-1400,700), glm::vec2(2, 2), glm::u8vec4(0xff, 0xff, 0xff, 0xff));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    glUseProgram(program.program);

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