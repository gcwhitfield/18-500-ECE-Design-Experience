#include "Shader.hpp"

Shader::Shader(std::string vertex, std::string fragment) {
    program = glCreateProgram();
    GLuint vertex_gl = -1U;
    GLuint fragment_gl = -1U;

    // code for compiling and linking shaders taken from chapter 5 of "Learn OpenGL - Graphics 
    // Programming" by Joey de Vries https://learnopengl.com/About
    { // create vertex shader
        vertex_gl = glCreateShader(GL_VERTEX_SHADER);
        const char *_vertex = vertex.c_str(); 
        glShaderSource(vertex_gl, 1, &(_vertex), NULL);
        glCompileShader(vertex_gl);
        int success;
        char info_log[512];
        glGetShaderiv(vertex_gl, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex_gl, 512, NULL, info_log);
            std::cout << "ERROR: vertex shader compilation failed\n" << info_log << std::endl;
            exit(1);
        }
        glAttachShader(program, vertex_gl);
    }
    // create fragment shader
    {
        fragment_gl = glCreateShader(GL_FRAGMENT_SHADER);
        const char *_fragment = fragment.c_str();
        glShaderSource(fragment_gl, 1, &(_fragment), NULL);
        glCompileShader(fragment_gl);
        int success;
        char info_log[512];
        glGetShaderiv(fragment_gl, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment_gl, 512, NULL, info_log);
            std::cout << "ERROR: fragment shader compilation failed\n" << info_log << std::endl;
            exit(1);
        }
        glAttachShader(program, fragment_gl);
    }
    glLinkProgram(program);
    glDeleteShader(vertex_gl); 
    glDeleteShader(fragment_gl);

    int success;
    char info_log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        std::cout << "Shader unsuccessfully linked: " << info_log << std::endl;
    }
}

Shader::~Shader() {
    glDeleteProgram(program);
    program = 0;
}