#include "MainMenuMode.hpp"

MainMenuMode::MainMenuMode() {
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