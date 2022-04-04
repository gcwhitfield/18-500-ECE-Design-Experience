#include "Shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <iostream>

#ifndef TEXT_RENDER_PROGRAM
#define TEXT_RENDER_PROGRAM
struct TextRenderProgram : Shader {
    TextRenderProgram();
    ~TextRenderProgram() {};
    
    // inputs to vertex shader
    GLuint position_vec4 = -1U;
    GLuint color_vec4 = -1U;
    GLuint tex_coords_vec2 = -1U;

    // uniforms
    GLuint OBJECT_TO_CLIP_MAT4 = -1U;
};

#endif