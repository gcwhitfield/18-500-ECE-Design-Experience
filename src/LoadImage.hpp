#ifndef LOAD_IMAGE
#define LOAD_IMAGE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <iostream>
#include <string>

struct LoadImage {
    static void load_img(GLuint *tex, std::string img);
};

#endif