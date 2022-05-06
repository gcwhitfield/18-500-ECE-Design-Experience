#include "Beatmap.hpp"

// the maxmium time window (in seconds) that the game will be able to receive an input from the
// player for hitting a note
float MAX_INPUT_THRESHOLD = 0.5; 

Beatmap::Beatmap() {

}

// code for reading file and loading into Json object taken from jsoncpp documentation
// https://github.com/open-source-parsers/jsoncpp/blob/master/example/readFromStream/readFromStream.cpp
Beatmap::Beatmap(std::string beatmap_file_path) {
    Json::Value root;
    std::ifstream ifs(beatmap_file_path.c_str(), std::ifstream::binary);
    size_t len = 0;
    std::string line;
    // 1) read the entire file, put into string
    // 1.1) get the size of the string
    while(getline(ifs, line)) {
        len += line.size();
    }
    // 1.2) now that we have the size, allocate a new string of size 'len' and put the contents
    // of the file inside
    ifs.clear();
    ifs.seekg(ifs.beg); // go back to the beginning of the file
    size_t i = 0;
    std::string data(len, ' '); // the contents of the json file
    while (ifs.is_open()) {
        while (getline(ifs, line)) {
            for (size_t k = 0; k < line.size(); k++) {
                data[i] = line[k];
                i++;
            }
        }
        ifs.close();
    }

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    JSONCPP_STRING errs;
    if (!reader->parse(data.c_str(), data.c_str() + data.size(), &root, &errs)) {
        std::cout << "Failed reading beatmap JSON" << std::endl;
        std::cout << errs << std::endl;
        exit(1);
    }

    // 2) place the data from JSON into Beatmap member variables
    BPM = root["BPM"].asInt();
    beats.resize(root["beats"].size());
    for (size_t k = 0; k < root["beats"].size(); k++)
    {
        Json::Value b = root["beats"];
        beats[k].first.location = (Beatmap::BeatLocation)b[(int)k].get("locations", Json::Value(0)).asInt();
        beats[k].first.time = (float)b[(int)k].get("time", Json::Value(0.0f)).asFloat();
    }
}

Beatmap::~Beatmap() {
    
}

void Beatmap::load(std::string filePath) {
    (void) filePath;
}

void Beatmap::draw(std::vector<Vertex> &vertices, const glm::uvec2 &drawable_size) {
    glm::vec2 judgement_pos(-200, -400);
    float horz_spacing = 200;
    glm::vec2 size(80, 80); // size of the notes
    size.x /= drawable_size.x;
    size.y /= drawable_size.y;

    glm::u8vec4 drum_0_note_color(0xff, 0x00, 0xff, 0xff);
    glm::u8vec4 drum_1_note_color(0x00, 0xff, 0xff, 0xff);
    glm::u8vec4 drum_2_note_color(0xff, 0xff, 0x00, 0xff);
    glm::u8vec4 drum_3_note_color(0x00, 0x00, 0xff, 0xff);

    // draw the notes that are currently flying towards the player
    for (size_t i = 0; i < beats.size(); i++) {
        std::pair<Beatmap::Beat, bool> *beat = &(beats[i]);
        if (!(beat->second)) { // draw the beat
            float scroll_speed = 20.0f;
            float starting_height = scroll_speed * beat->first.time;
            float curr_height = starting_height - scroll_speed*t;
            curr_height *= scroll_speed;

            // change the color of the notes based on drum location
            glm::u8vec4 col(0xff, 0xff, 0xff, 0xff);
            {
                switch (beat->first.location)
                {
                    case LEFT:
                        col = drum_0_note_color;
                        break;
                    case DOWN:
                        col = drum_1_note_color;
                        break;
                    case UP:
                        col = drum_2_note_color;
                        break;
                    case RIGHT:
                        col = drum_3_note_color;
                        break;
                }
            }

            glm::vec2 pos(horz_spacing * (int)beat->first.location + judgement_pos.x, curr_height + judgement_pos.y);
            pos.x /= drawable_size.x;
            pos.y /= drawable_size.y;
            draw_rectangle(vertices, pos, size, col);
        }
    }

    // change size of judgement note depending on whether the drum hit affect is active
    float size_drum_0_offset = 1.0f;
    float size_drum_1_offset = 1.0f;
    float size_drum_2_offset = 1.0f;
    float size_drum_3_offset = 1.0f;
    float size_offset = 1.3;
    {
        if (t_drum_0 > 0) size_drum_0_offset = size_offset;
        if (t_drum_1 > 0) size_drum_1_offset = size_offset;
        if (t_drum_2 > 0) size_drum_2_offset = size_offset;
        if (t_drum_3 > 0) size_drum_3_offset = size_offset;
    }
    // draw the judgement notes
    judgement_pos.x /= drawable_size.x;
    judgement_pos.y /= drawable_size.y;
    draw_rectangle(vertices, judgement_pos, size*size_drum_0_offset, drum_0_note_color);
    draw_rectangle(vertices, glm::vec2(judgement_pos.x + horz_spacing/drawable_size.x, judgement_pos.y), size*size_drum_1_offset, drum_1_note_color);
    draw_rectangle(vertices, glm::vec2(judgement_pos.x + 2*horz_spacing/drawable_size.x, judgement_pos.y), size*size_drum_2_offset, drum_2_note_color);
    draw_rectangle(vertices, glm::vec2(judgement_pos.x + 3*horz_spacing/drawable_size.x, judgement_pos.y), size*size_drum_3_offset, drum_3_note_color);
}

bool Beatmap::update(float elapsed) {
    bool result = true;
    
    // validate that the beatmap is being displayed correctly
    {
        // all of the beats that occur after beats[next_beat] will occur in the future
        for (size_t i = next_beat; i < beats.size(); i++) {
            assert(beats[i].first.time >= t);

        }
        for (size_t i = 0; i < next_beat; i++) {
            assert(beats[i].first.time <= t);
        }
    }

    { // determine whether the player has missed a note
        float t_until_del_after_judgement = 1.0; // seconds
        for (size_t i = 0; i < beats.size(); i++) {
            if (!beats[i].second && beats[i].first.time + t_until_del_after_judgement < t) {
                beats[i] = std::make_pair(beats[i].first, true);
                result = false;
            }
        }
    }

    t += elapsed;
    while (beats[next_beat].first.time < t) {
        next_beat ++;
    }

    // update drum hit indicators
    {
        t_drum_0 -= elapsed;
        t_drum_1 -= elapsed;
        t_drum_2 -= elapsed;
        t_drum_3 -= elapsed;
    }

    return result;
}

float Beatmap::process_beat(BeatLocation location) {
    // set hit effect timer for the drum that was hit. This determines how long the 
    // effect is played for
    {
        float drum_hit_effect_len = 0.1f; // in seconds
        switch (location)
        {
            case LEFT:
                t_drum_0 = drum_hit_effect_len;
                break;
            case DOWN:
                t_drum_1 = drum_hit_effect_len;
                break;
            case UP:
                t_drum_2 = drum_hit_effect_len;
                break;
            case RIGHT:
                t_drum_3 = drum_hit_effect_len;
                break;
        }
    }

    // mark incoming beats as being 'hit' (beats[i].second gets set to 'true') if the user has hit 
    // the correct drum at the correct time
    {
        size_t initial_beat = next_beat > 1 ? next_beat - 1 : next_beat;
        // check for beats coming in the future
        for (size_t i = initial_beat; i < beats.size(); i++) {
            if (beats[i].first.location != location) continue;
            if (beats[i].second) continue;
            Beat &curr_beat = beats[i].first;
            float time_diff = curr_beat.time - t;
            if (MAX_INPUT_THRESHOLD < abs(time_diff)) {
                // if the player completed misses a note, then skip it and go to the next note
                // if the player hits the drum way too early, then do nothing
                if (time_diff < 0) {
                    continue; // player hits way too late
                } else {
                    break; // player hits way too early
                }
            }
            else {
                beats[i] = std::make_pair(beats[i].first, true);
                assert(beats[i].second);
                return abs(time_diff);
            }
        }
    }
    return -1;
}