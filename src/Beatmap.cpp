#include "Beatmap.hpp"

Beatmap::Beatmap() {

}

Beatmap::~Beatmap() {
    
}

void Beatmap::load(std::string filePath) {
    (void) filePath;
}

void Beatmap::draw(std::vector<Vertex> &vertices, const glm::uvec2 &drawable_size) {
    for (size_t i = 0; i < beats.size(); i++) {
        Beatmap::Beat beat = beats[i];
        if (t < beat.time) { // draw the beat
            float scroll_speed = 20.0f;
            float desired_height = -500;
            float starting_height = scroll_speed * beat.time;
            float curr_height = starting_height - scroll_speed*t;
            curr_height *= scroll_speed;
            float horz_spacing = 200;
            glm::vec2 size(80, 80);
            size.x /= drawable_size.x;
            size.y /= drawable_size.y;
            glm::vec2 pos(horz_spacing * (int)beat.location - 300, curr_height + desired_height);
            pos.x /= drawable_size.x;
            pos.y /= drawable_size.y;
            draw_rectangle(vertices, pos, size, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
        }
    }
}

void Beatmap::update(float elapsed) {
    t += elapsed;
}
