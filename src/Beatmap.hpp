#include "Vertex.hpp"
#include <json/json.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifndef BEATMAP
#define BEATMAP
struct Beatmap {

    enum BeatLocation {
        LEFT = 0,
        DOWN = 1,
        UP = 2,
        RIGHT = 3
    };

    struct Beat {
        BeatLocation location; // which lane does the beat occur in?
        float time; // when does the beat occur?
    };

    struct BeatFileData {
        std::string name;
        size_t BPM;
        std::vector<Beat> beats;
    };

    size_t BPM = 0;
    float t = 0.0f; // the current time that has elapsed into the song in seconds

    Beatmap();
    Beatmap(std::string beatmap_file_path); // loads beatmap from JSON file 
    Beatmap(std::vector<Beatmap::Beat> &beats, size_t bpm); // initializes the Beatmap with a given 'beats' queue
    ~Beatmap();


    // the beats in 'beats' are ordered based on the time that they occur in the song. Beats at 
    // lower indices occur earlier in the song, beats at later indices occur later
    // the first element contains the beat info
    // the second element contains a bool, which flags whether the beet has been hit by the user
    std::vector<std::pair<Beat, bool>> beats;
    size_t next_beat = 0; // an index into 'beats' that corresponds to the next beat after beatmap.t

    // given a path to a song JSON file, loads the data into the 'beats' vector
    void load(std::string filePath);

    // draws the beatmap to the screen
    void draw(std::vector<Vertex> &vertices, const glm::uvec2 &drawable_size);

    // called every frame
    void update(float elapsed);

    // Returns the amount of time that will elapse after beatmap.t until the next occurrence of a 
    // beat at 'location'. If the next occurrence takes too long, this function will return -1.
    // Additionally, process_beat will flag the second element of the beat to 'true', which means 
    // that the beat has been seen and it should no longer be drawn 
    float process_beat(BeatLocation location);
};

#endif