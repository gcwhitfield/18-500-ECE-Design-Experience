// The overall structure of this file was inspried by the Sound.cpp file from the game 3 base case 
// from the Computer Game Programming course at CMU https://github.com/15-466/15-466-f21-base3/blob/main/Sound.cpp
// 
// A lot of the portaudio code in this file was taken from the portaudio tutorials from 
// http://www.portaudio.com/docs/. Specifically, the code for Sound::Init, Sound::DeInit, Sound::paTestData, 
// and stream_callback were taken from the portaudio documentation

#include "Sound.hpp"

const size_t NUM_CHANNELS = 2;
static std::mutex sound_mutex;
static PaStream *stream;
static Sound::paTestData stream_data;
static std::list<Sound::PlayingSample *> playing_samples;

// This function will be called by the PortAudio engine when audio is needed. It 
// may be called at interrupt level on some machines so do not do anything that could mess 
// up the system, such as malloc() or free()
int stream_callback(const void *input, void *output, unsigned long frame_count,  
    const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags status_flags, void *user_data){
    memset((float*)output, 0, frame_count * NUM_CHANNELS * sizeof(float));
    sound_mutex.lock();
    // initialize the data in 'output' to zero, to make sure that we don't get any crazy popping 
    // noises
    // line taken from libaudiodecoder documentation: https://github.com/asantoni/libaudiodecoder/blob/master/examples/playsong/playsong.cpp

    // cast data passed through stream to our structure
    Sound::paTestData *data = (Sound::paTestData*) user_data;
    (void)data;
    float *out = (float*)output;
    (void)out;
    (void) input;
    (void) time_info;
    (void) status_flags;

    for (auto s = data->playing_samples->begin(); s != data->playing_samples->end(); /* updated in loop */) {
        Sound::PlayingSample* sample = *s;

        for (size_t i = 0; i < frame_count * NUM_CHANNELS; i++) {
            if (sample->stop) break;
            
            out[i] += sample->data.data()[sample->curr_index];

            if (out[i] > 1.0f) {
                out[i] = 1.0f;
            } else if (out[i] < -1.0f) {
                out[i] = -1.0f;
            }

            // loop samples forever if sample->loop is true. remove old samples from the
            // 'playing_samples' list if the sample has finished playing
            sample->curr_index ++;
            if (sample->curr_index >= sample->data.size()) {
                if (sample->loop) { // loop back to the beginning
                    sample->curr_index = 0;
                } else { // remove the sample from the list
                    sample->stop = true;
                }
            }
        }
        s++;
        if (sample->stop) {
            data->playing_samples->remove(sample);
            delete sample;
        }
    }

    sound_mutex.unlock();
    return 0;
}
void Sound::init() {

    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Error initializing Portaudio" << std::endl;
        std::cerr << Pa_GetErrorText(err) << std::endl;
        exit(1);
    }
    stream_data.playing_samples = &playing_samples;

    size_t sample_rate = 44100;
    // Open an audio I/O stream 
    err = Pa_OpenDefaultStream(&stream, 
        0, // no input channels
        2, // stero output
        paFloat32, // 32 bit floating point output
        sample_rate, 
        1024, // frames per buffer, i.e. the number of sample 
              // frames that PortAudio will request from the callback. Many apps
              // may want to use paFramesPerBufferUnspecified, which tells 
              // PortAudio to pick the best, possibly changing, buffer size
        &stream_callback,
        &stream_data); // data that is passed to the callback function
    if (err != paNoError) {
        std::cerr << "Error opening stream for Portaudio" << std::endl;
        std::cerr << Pa_GetErrorText(err) << std::endl;
        exit(1);
    }
    return;
}

void Sound::de_init() {
    Pa_CloseStream(stream);
    PaError err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "Error with terminating PortAudio" << std::endl;
        std::cerr << Pa_GetErrorText(err) << std::endl;
    }
}

void Sound::begin_play() {
    if (!Pa_IsStreamActive(stream)) {
        PaError err = Pa_StartStream(stream);
        if (err != paNoError) {
            if (err != paNoError) {
            std::cerr << "Error with starting PortAudio stream" << std::endl;
            std::cerr << Pa_GetErrorText(err) << std::endl;
            }
        }
    }
}

void Sound::play_test_sound() {
    PaError err = Pa_StartStream(stream);
    if (err != paNoError) {
        if (err != paNoError) {
        std::cerr << "Error with starting PortAudio stream" << std::endl;
        std::cerr << Pa_GetErrorText(err) << std::endl;
        }
    }
}

void Sound::play(Sound::PlayingSample *sample) {
    sound_mutex.lock();
    playing_samples.push_back(sample);
    sound_mutex.unlock();
    if (playing_samples.size() == 1) {
        Sound::begin_play();
    }
}

void Sound::stop(Sound::PlayingSample *sample) {
    sound_mutex.lock();
    sample->stop = true; 
    // the sample will be removed from the playing samples vector at the next audio callback
    sound_mutex.unlock();
}