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
        std::pair<Beatmap::Beat, bool> *beat = &(beats[i]);
        if (t < beat->first.time && !beat->second) { // draw the beat
            float scroll_speed = 20.0f;
            float desired_height = -500;
            float starting_height = scroll_speed * beat->first.time;
            float curr_height = starting_height - scroll_speed*t;
            curr_height *= scroll_speed;
            float horz_spacing = 200;
            glm::vec2 size(80, 80);
            size.x /= drawable_size.x;
            size.y /= drawable_size.y;
            glm::vec2 pos(horz_spacing * (int)beat->first.location - 300, curr_height + desired_height);
            pos.x /= drawable_size.x;
            pos.y /= drawable_size.y;
            draw_rectangle(vertices, pos, size, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
        }
    }
}

void Beatmap::update(float elapsed) {
    t += elapsed;
    while (t < beats[next_beat].first.time) {
        next_beat ++;
    }
}

float Beatmap::process_beat(BeatLocation location) {
    float MAX_INPUT_THRESHOLD = 1.0; // seconds
    // check for beats coming in the future
    for (size_t i = next_beat; i < beats.size(); i++) {
        Beat &curr_beat = beats[i].first;
        float next_time = curr_beat.time - t;
        if (MAX_INPUT_THRESHOLD < next_time) {
            break;
        }
        if (curr_beat.location != location) continue;
        else {
            beats[i].second = true;
            return next_time;
        }
    }
    // check beats that have just occurred
    for (size_t i = next_beat - 1; i >= 0; i--) {
        Beat &curr_beat = beats[i].first;
        float prev_time = t - curr_beat.time;
        if (MAX_INPUT_THRESHOLD < prev_time) {
            return -1;
        }
        if (curr_beat.location != location) continue;
        else {
            beats[i].second = true;
            return prev_time;
        }
    }
    return -1;
}