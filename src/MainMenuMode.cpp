#include "MainMenuMode.hpp"

// define image file paths
static std::string background_img("./art/images/background.png");

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

    { // import background texture
        LoadImage::load_img(&background_texture, background_img);
        print_gl_errors();
    }
}

MainMenuMode::~MainMenuMode() {

}

void MainMenuMode::update(float elapsed) {
    (void) elapsed;
}

void MainMenuMode::handle_key(GLFWwindow *window, int key, int scancode, int actions, int mods) {
    (void) window;
    (void) key;
    (void) scancode;
    (void) actions;
    (void) mods;
}

void MainMenuMode::handle_drum(std::vector<char> hits) {
    (void) hits;
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

    { // draw solid color rectangles 
        // use a solid white texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, white_texture);

        // run the OpenGL pipeline
        glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));

        print_gl_errors();
        glBindTexture(GL_TEXTURE_2D, 0); // unbind white texture
    }

    // draw text
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBindVertexArray(vertex_array_object);
        text_renderer.draw(drawable_size, "Rendering text!", glm::vec2(-200,500), glm::vec2(2, 2), glm::u8vec4(0xff, 0xff, 0xff, 0xff));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(0);    
    glUseProgram(0);
}