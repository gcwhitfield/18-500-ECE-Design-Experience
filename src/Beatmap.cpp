#include "Beatmap.hpp"

// the maxmium time window (in seconds) that the game will be able to receive an input from the
// player for hitting a note
float MAX_INPUT_THRESHOLD = 1.0; 

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
        beats[k].first.location = (Beatmap::BeatLocation)b[(int)k].get("location", Json::Value(0)).asInt();
        beats[k].first.time = (float)b[(int)k].get("time", Json::Value(0.0f)).asFloat();
    }
}

Beatmap::~Beatmap() {
    
}

void Beatmap::load(std::string filePath) {
    (void) filePath;
}

void Beatmap::draw(std::vector<Vertex> &vertices, const glm::uvec2 &drawable_size) {
    // draw the notes that are currently flying towards the player
    glm::vec2 judgement_pos(-200, -400);
    float horz_spacing = 200;
    glm::vec2 size(80, 80); // size of the notes
    size.x /= drawable_size.x;
    size.y /= drawable_size.y;
    float t_until_del_after_judgement = 1.0; // seconds
    for (size_t i = 0; i < beats.size(); i++) {
        std::pair<Beatmap::Beat, bool> *beat = &(beats[i]);
        if (t - t_until_del_after_judgement < beat->first.time && !beat->second) { // draw the beat
            float scroll_speed = 20.0f;
            float starting_height = scroll_speed * beat->first.time;
            float curr_height = starting_height - scroll_speed*t;
            curr_height *= scroll_speed;
            glm::vec2 pos(horz_spacing * (int)beat->first.location + judgement_pos.x, curr_height + judgement_pos.y);
            pos.x /= drawable_size.x;
            pos.y /= drawable_size.y;
            draw_rectangle(vertices, pos, size, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
        }
    }
    // draw the judgement notes
    judgement_pos.x /= drawable_size.x;
    judgement_pos.y /= drawable_size.y;
    draw_rectangle(vertices, judgement_pos, size, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
    draw_rectangle(vertices, glm::vec2(judgement_pos.x + horz_spacing/drawable_size.x, judgement_pos.y), size, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
    draw_rectangle(vertices, glm::vec2(judgement_pos.x + 2*horz_spacing/drawable_size.x, judgement_pos.y), size, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
    draw_rectangle(vertices, glm::vec2(judgement_pos.x + 3*horz_spacing/drawable_size.x, judgement_pos.y), size, glm::u8vec4(0xff, 0xff, 0xff, 0xff));
}

void Beatmap::update(float elapsed) {
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

    t += elapsed;
    while (beats[next_beat].first.time  < t) {
        next_beat ++;
    }
}

float Beatmap::process_beat(BeatLocation location) {
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
            std::cout << "note has been hit late" << std::endl;
            return prev_time;
        }
    }
    return -1;
}