#include "ScoreScreenMode.hpp"

ScoreScreenMode::ScoreScreenMode() {

}

ScoreScreenMode::~ScoreScreenMode() {

}

void ScoreScreenMode::draw(glm::uvec2 const &drawable_size) {
    (void) drawable_size;
}

void ScoreScreenMode::handle_key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    (void) window;
    (void) key;
    (void) scancode;
    (void) action;
    (void) mods;
}

void ScoreScreenMode::update(float elapsed) {
    (void) elapsed;
}