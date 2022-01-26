#include "Mode.hpp"

std::shared_ptr<Mode> Mode::current;

void Mode::set_current(std::shared_ptr<Mode> const &new_current) {
    current = new_current;
}

void Mode::update(float elapsed) {
    (void)elapsed;
}

void Mode::handle_key(GLFWwindow *window, int key, int scancode, int action, int mods) {
   (void)window;
   (void)key;
   (void)scancode;
   (void)action;
   (void)mods;
}

void Mode::draw(glm::uvec2 const &drawable_size) {
    (void)drawable_size;
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}