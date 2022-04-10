#include "FadingScreenTransition.hpp"

void FadingScreenTransition::play(ScreenTransitionAnimType anim_type_, float anim_time_, glm::u8vec4 color_) {
    t = 0.001f;
    color = color_;
    anim_time = anim_time_;
    anim_type = anim_type_;
}

void FadingScreenTransition::update(float elapsed) {
    if (is_active()) {
        t += elapsed;
    }
}

void FadingScreenTransition::draw(glm::uvec2 const &drawable_size) {
    if (is_active()) {
        vertices.clear();

        // interpolate the alpha channel over time
        if (anim_type == ScreenTransitionAnimType::OPEN) {
            color.a = 0xff*(1.0f - (t/anim_time));
        } else if (anim_type == ScreenTransitionAnimType::CLOSE) {
            color.a = 0xff*(t/anim_time);
        }
        
        draw_rectangle(vertices, glm::vec2(0,0), glm::vec2(1,1), color);
    }
}