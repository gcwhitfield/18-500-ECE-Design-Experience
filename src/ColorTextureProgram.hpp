#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <iostream>

// ColorTexture program stores information about the vertex shader, fragment shader, uniforms, and 
// input arguments for an OpenGL program. Much of the code in ColorTexutreProgram.hpp/cpp
// comes from the Learning OpenGL textbook by Joey de Vries and the game 0 base code from 
// ixchow https://github.com/15-466/15-466-f21-base0/blob/main/main.cpp. 
struct ColorTextureProgram {
    ColorTextureProgram();
    ~ColorTextureProgram();

    // inputs to vertex shader
    GLuint program = -1U;
    GLuint position_vec4 = -1U;
    GLuint color_vec4 = -1U;
    GLuint tex_coords_vec2 = -1U;

    // uniforms
    GLuint OBJECT_TO_CLIP_MAT4 = -1U;
};