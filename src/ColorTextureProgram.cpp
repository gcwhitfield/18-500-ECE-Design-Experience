#include "ColorTextureProgram.hpp"

// 'vertex_shader' and 'fragment_shader' are written in GLSL
const static char *vertex_shader = "#version 330 core\n"
            "in vec4 pos;\n"
            "in vec4 color;\n"
            "in vec2 tex_coord;\n"
            "out vec4 Color;\n"
            "out vec2 Tex_coord;\n"
            "void main() {\n"
            "   gl_Position = vec4(pos.x, pos.y, pos.z, 1);\n"
            "Color = color;\n"
                "Tex_coord = tex_coord;\n"
            "}";
const static char *fragment_shader = "#version 330 core\n"
            "uniform sampler2D TEX;\n"
            "in vec4 Color;\n"
            "in vec2 Tex_coord;\n"
            "out vec4 frag_color;\n"
            "void main() {\n"
            "   frag_color = texture(TEX, Tex_coord) * Color;\n"
            "}";
            
ColorTextureProgram::ColorTextureProgram() :
    Shader(vertex_shader, fragment_shader) {
    
    //look up the locations of vertex attributes:
    // taken from "ColorTextureProgram.cpp" of 15-466 game0 base code https://github.com/15-466/15-466-f21-base0
	position_vec4 = glGetAttribLocation(program, "pos");
	color_vec4 = glGetAttribLocation(program, "color");
	tex_coords_vec2 = glGetAttribLocation(program, "tex_coord");

    // set TEX to refer to the texture binding at location 0 - from "game 0" base code
    glUseProgram(program); // step 1) activate the program
    GLuint TEX_sampler_2D = glGetUniformLocation(program, "TEX");
    glUniform1i(TEX_sampler_2D, 0); // step 2) bind TEX to location 0
    glUseProgram(0); // step 3) unbind the program
}