#ifndef SOUND
#define SOUND

#include "portaudio.h"
#include "audiodecoder.h"

#include <chrono>
#include <iostream>
#include <vector>
#include <list>
#include <mutex>

// this Sound class is a simple interface for playing sounds in our game with Portaudio
namespace Sound {
        struct Sample {
            Sample(std::string file_path) {
                audio = new AudioDecoder(file_path.c_str());
                bool successful = false;
                if (audio->open() == AUDIODECODER_OK) {
                    successful = true;
                }

                if (!successful) { // try opening as wav if mp3 not found, vice versa
                    int mp3 = file_path.find(".mp3");
                    int wav = file_path.find(".wav");
                    if (mp3 != -1) {
                        file_path = file_path.substr(0, mp3) + ".wav";
                    } else if (wav != -1) {
                        file_path = file_path.substr(0, wav) + ".mp3";
                    } else {
                        std::cerr << "Invalid audio file: " << file_path << std::endl;
                        exit(1);
                    }
                    delete audio;
                    audio = new AudioDecoder(file_path.c_str());
                    if (audio->open() == AUDIODECODER_OK) {
                        successful = true;
                    }
                }

                if (!successful) {
                    std::cerr << "Could not open audio file: " << file_path << std::endl;
                    exit(1); 
                }
                
                // if the file is an mp3, try looking for a wav instead
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
            // opportunity and it will delete itself
            bool pause = false; // when set to true, this sample will stop playing at the next available
            // opportunity. Unlike the 'stop' parameter, the 'pause' parameter will NOT cause the 
            // sample to get deleted
            bool loop = false; // when set to true, this sample will loop forever until it's stopped
            // TODO: add pan?
        };

        struct SoundStreamData{
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
        
        // resets the sound thread's internal timer (used for debuggin)
        void reset_timer();

        // ---------- private ----------
        // begins playback of PortAudio stream.
        void begin_play();
};

#endif