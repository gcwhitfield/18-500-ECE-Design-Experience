#include "Vertex.hpp"

#include <vector>
#include <string>
#include <iostream>

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

    Beatmap();
    Beatmap(std::vector<Beatmap::Beat> beats); // initializes the Beatmap with a given 'beats' queue
    ~Beatmap();

    float t = 0.0f; // the current time that has elapsed into the song

    // the beats in 'beats' are ordered based on the time that they occur in the song. Beats at 
    // lower indices occur earlier in the song, beats at later indices occur later
    std::vector<Beat> beats;

    // given a path to a song JSON file, loads the data into the 'beats' vector
    void load(std::string filePath);

    // draws the beatmap to the screen
    void draw(std::vector<Vertex> &vertices, const glm::uvec2 &drawable_size);

    // called every frame
    void update(float elapsed);
};