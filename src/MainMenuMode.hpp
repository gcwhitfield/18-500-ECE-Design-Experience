#include "Mode.hpp"

#include <glm.hpp>

#ifndef MAIN_MENU_MODE
#define MAIN_MENU_MODE

struct ScoreScreenMode : Mode 
{
    virtual void update(float elapsed) override;

    virtual void handle_key(
        GLFWwindow *window, 
        int key,
        int scancode, 
        int action, 
        int mods) override;
        
    virtual void draw(glm::uvec2 const &drawable_size) override;
};

#endif