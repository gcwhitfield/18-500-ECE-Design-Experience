#include "ColorTextureProgram.hpp"

ColorTextureProgram::ColorTextureProgram() {
    program = glCreateProgram();
    GLuint vertex = -1U;
    GLuint fragment = -1U;

    // code for compiling and linking shaders taken from chapter 5 of "Learn OpenGL - Graphics 
    // Programming" by Joey de Vries https://learnopengl.com/About
    { // create vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        const char *vertex_shader = "#version 330 core\n"
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
        glShaderSource(vertex, 1, &vertex_shader, NULL);
        glCompileShader(vertex);
        int success;
        char info_log[512];
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, info_log);
            std::cout << "ERROR: vertex shader compilation failed\n" << info_log << std::endl;
            exit(1);
        }
        glAttachShader(program, vertex);
    }
    // create fragment shader
    {
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        const char *fragment_shader = "#version 330 core\n"
            "uniform sampler2D TEX;\n"
            "in vec4 Color;\n"
            "in vec2 Tex_coord;\n"
            "out vec4 frag_color;\n"
            "void main() {\n"
            "   frag_color = texture(TEX, Tex_coord) * Color;\n"
            "}";
        glShaderSource(fragment, 1, &fragment_shader, NULL);
        glCompileShader(fragment);
        int success;
        char info_log[512];
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, info_log);
            std::cout << "ERROR: fragment shader compilation failed\n" << info_log << std::endl;
            exit(1);
        }
        glAttachShader(program, fragment);
    }
    glLinkProgram(program);
    glDeleteShader(vertex); 
    glDeleteShader(fragment);

    int success;
    char info_log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        std::cout << "Shader unsuccessfully linked: " << info_log << std::endl;
    }
    
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

ColorTextureProgram::~ColorTextureProgram() {
    glDeleteProgram(program);
    program = 0;
}