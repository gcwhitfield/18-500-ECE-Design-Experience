#include "MainMenuMode.hpp"

// define image file paths
static std::string background_img("./art/images/main menu background.png");
static std::string logo_img("./art/images/logo.png");
static std::string hit_drums_to_begin_img("./art/images/hit drums to begin.png");

// import sounds
static Sound::Sample initialization_sound("./art/sounds/initialization_noise.mp3");
static Sound::Sample bloop_cmaj("./art/sounds/bloop_cmaj911_ascending.mp3");


MainMenuMode::MainMenuMode() {
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
    
    { // initialize drums
        drums = new DrumPeripheral();
    }

    { // import background texture
        LoadImage::load_img(&background_texture, background_img);
        print_gl_errors();
    }

    { // import logo texture
        LoadImage::load_img(&logo_texture, logo_img);
        print_gl_errors();
    }

    { // import hit drums to continue texture
        LoadImage::load_img(&hit_drums_to_begin_texture, hit_drums_to_begin_img);
        print_gl_errors();
    }


    { // initialize fading screen transition
        fading_screen_transition.play(
            FadingScreenTransition::ScreenTransitionAnimType::OPEN,
            4.0f,
            glm::u8vec4(0xff, 0xff, 0xff, 0xff)
        );
    }

    { // play initialization sound
        Sound::PlayingSample *init_noise = new Sound::PlayingSample(&initialization_sound);
        Sound::play(init_noise);
    }
}

MainMenuMode::~MainMenuMode() {

}

void MainMenuMode::update(float elapsed) {

    { // modulate the alpha channel "hit a drum to begin" text over time
        float modulation_speed = 2;
        t += elapsed * modulation_speed;
        if (t > 3.1415926 * 2) {
            t -= 3.1415926 * 2;
        }
    }

    fading_screen_transition.update(elapsed);
    drums->update(elapsed);
    switch (curr_state) {
        case OPEN:
            if (fading_screen_transition.is_finished()) {
                curr_state = WAIT;
            }
            break;
        case WAIT:
            // next state is set from handle_key
            break;
        case CLOSE:
            // transition to the next scene if the scene transition animation is finished playing
            if (fading_screen_transition.is_finished()) {
                Mode::set_current(std::make_shared<SongSelectionMode>());
            }
            break;
    }
}

// if the main menu is ready, goes to song selection mode
void MainMenuMode::go_to_song_selection_mode() {
    if (fading_screen_transition.is_finished()) {
        fading_screen_transition.play(
            FadingScreenTransition::ScreenTransitionAnimType::CLOSE,
            4.0f,
            glm::u8vec4(0xff, 0xff, 0xff, 0xff)
        );
        curr_state = CLOSE;
        { // play bloops cmaj911 sound
            Sound::PlayingSample *bloop_confirm = new Sound::PlayingSample(&bloop_cmaj);
            Sound::play(bloop_confirm);
        }
    }
}

void MainMenuMode::handle_key(GLFWwindow *window, int key, int scancode, int actions, int mods) {
    (void) window;
    (void) scancode;
    (void) mods;

    if (actions == Input::KeyAction::PRESS) {
        switch (curr_state) {
            case WAIT:
                if (key == Input::KeyCode::ENTER) {
                    go_to_song_selection_mode();
                 }
                break;
            default:
                break;
        }
    }
}

void MainMenuMode::handle_drum(std::vector<char> hits) {
    (void) hits;
    // when any of the drums are hit, transition into song selection mode
    switch (curr_state) {
        case WAIT:
            go_to_song_selection_mode();
            break;
        default:
            break;
    }
}

void MainMenuMode::draw(glm::uvec2 const &drawable_size) {
    // drawing starter code taken from "game 0 base code"
    // https://github.com/15-466/15-466-f21-base0

    // the "draw_rectangle" functino will emplace vertices on to the "vertices" vector each frame.
    // "vertices" must be cleared at the beginning of each frame so that old vertices are not drawn
    // continuously to the screen
    vertices.clear();

    (void) drawable_size;
    glUseProgram(program.program); // tell OpenGL to draw using "ColorTextureProgram"
    glClearColor(0.5, 0.5, 0.5, 1); // set background color
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);

    // the next line sets the alpha blending function. the alpha blending function determines how
    // transparent or semi-transparent object get drawn on top of each other
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // send the vertices to the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // tell OpenGL to use the vertex array object that we configued above in the constructor 
    glBindVertexArray(vertex_array_object);

    { // draw background image
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

    { // draw the hit it logo
        vertices.clear();
        draw_rectangle(vertices, glm::vec2(0.0, 0.0), glm::vec2(0.5, 0.392), glm::u8vec4(0xff, 0xff, 0xff, 0xff));

        // send the vertices to the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindVertexArray(vertex_array_object);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, logo_texture);

        // run the OpenGL pipeline
        glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
        print_gl_errors();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    { // draw "hit drums to begin" text
        vertices.clear();
        draw_rectangle(vertices, glm::vec2(0.0, -0.5), glm::vec2(0.8, 0.3), 
            glm::u8vec4(0xff, 0xff, 0xff, 
                0xff * ((1 + sinf(t)) / 2) // modulate the alpha channel of text over time
                ));

        // send the vertices to the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindVertexArray(vertex_array_object);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, hit_drums_to_begin_texture);

        // run the OpenGL pipeline
        glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
        print_gl_errors();
        glBindTexture(GL_TEXTURE_2D, 0);
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