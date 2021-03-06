#include "Shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <iostream>

#ifndef COLOR_TEXTURE_PROGRAM
#define COLOR_TEXTURE_PROGRAM

struct ColorTextureProgram : Shader {
    ColorTextureProgram();
    ~ColorTextureProgram() {};

    // inputs to vertex shader
    GLuint position_vec4 = -1U;
    GLuint color_vec4 = -1U;
    GLuint tex_coords_vec2 = -1U;

    // uniforms
    GLuint OBJECT_TO_CLIP_MAT4 = -1U;
};

#endif