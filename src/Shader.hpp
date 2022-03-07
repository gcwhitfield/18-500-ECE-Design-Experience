#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <iostream>
#include <string>

#ifndef SHADER
#define SHADER
// 'Shader' is a struct that stores information about the vertex shader and fragment shader 
//  for an OpenGL program. In the constructor of 'Shader', the vertex and fragment shaders get
// compiled and linked my OpenGL. Much of the code in Shader.cpp
// comes from the Learning OpenGL textbook by Joey de Vries and the game 0 base code from 
// ixchow https://github.com/15-466/15-466-f21-base0/blob/main/main.cpp. 
struct Shader {
    // 'vertex' is a string that contains the GLSL for the vertex pass
    // 'fragment' is a string that contains the GLSL for the fragment pass
    Shader(std::string vertex, std::string fragment);
    ~Shader();

    GLuint program = -1U;
};

#endif