#include "portaudio.h"
#include "audiodecoder.h"
#include <iostream>
#include <vector>
#include <list>
#include <mutex>

#ifndef SOUND
#define SOUND

// this Sound class is a simple interface for playing sounds in our game with Portaudio
namespace Sound {

        struct Sample {
            Sample(std::string file_path) {
                audio = new AudioDecoder(file_path.c_str());
                if (audio->open() != AUDIODECODER_OK) {
                    std::cerr << "Something went wrong trying to open the audio file : " << file_path << std::endl;
                    exit(1);
                }
                data.resize(audio->numSamples());
                audio->read(audio->numSamples(), data.data());
            }
            ~Sample() { delete audio; };
            std::vector<float> data;
            AudioDecoder *audio;
        };
         
        struct PlayingSample {
            PlayingSample(Sample *sample) : audio(*(sample->audio)), data(sample->data) {};
            ~PlayingSample(){ };
            AudioDecoder &audio;
            size_t curr_index = 0; // the current index of the sample that is being played
            std::vector<float> const &data;
            float volume;
            bool stop = false; // when set to true, this sample will stop playing at the next available 
            // opportunity
            bool loop = false; // when set to true, this sample will loop forever until it's stopped
            // TODO: add pan?
        };

        struct paTestData{
            float left_phase = 0;
            float right_phase = 0;
            std::list<PlayingSample*> *playing_samples;
        };

        void play(PlayingSample *sample);

        void stop(PlayingSample *sample);
        
        // this function must be called before using the sound interface
        void init();

        // call this function to clean up portaudio resources
        void de_init();
        
        void play_test_sound();

        // begins playback of PortAudio stream
        void begin_play();
};

#endif