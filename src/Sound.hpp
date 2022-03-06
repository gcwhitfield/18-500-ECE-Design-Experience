#include "portaudio.h"
#include "audiodecoder.h"
#include <iostream>
#include <vector>

// this Sound class is a simple interface for playing sounds in our game with Portaudio
struct Sound {
    Sound();
    ~Sound();
    struct PlayingSample {
        AudioDecoder *audio;
        size_t curr_index; // the current index of the sample that is being played
        std::vector<float> data;
        float volume;
        bool stop; // when set to true, this sample will stop playing at the next available 
        // opportunity
        bool loop; // when set to true, this sample will loop forever until it's stopped
        // TODO: add pan?
    };

    struct paTestData{
        float left_phase;
        float right_phase;
        std::vector<PlayingSample*> *playing_samples;
    };


    std::vector<PlayingSample *> playing_samples;

    void play(PlayingSample * sample);

    void stop(PlayingSample * sample);
    
    PaStream *stream;
    paTestData stream_data;

    // this function must be called before using the sound interface
    void init();

    // call this function to clean up portaudio resources
    void de_init();
    
    void play_test_sound();
};