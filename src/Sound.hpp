#include "portaudio.h"
#include "audiodecoder.h"
#include <iostream>

// this Sound class is a simple interface for playing sounds in our game with Portaudio
struct Sound {
    Sound();
    ~Sound();

    struct paTestData{
        float left_phase;
        float right_phase;
    };

    PaStream *stream;
    paTestData stream_data;

    // this function must be called before using the sound interface
    void init();

    // call this function to clean up portaudio resources
    void de_init();
    
    void play_test_sound();
};