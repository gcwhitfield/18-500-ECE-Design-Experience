#include "Sound.hpp"

// a lot of the portaudio code in this file was copied from the portaudio tutorials from 
// http://www.portaudio.com/docs/. Specifically, the code for Sound::Init, Sound::DeInit, Sound::paTestData, 
// and stream_callback were taken from the portaudio documentation

// This function will be called by the PortAudio engine when audio is needed. It 
// may be called at interrupt level on some machines so do not do anything that could mess 
// up the system, such as malloc() or free()
int stream_callback(const void *input, void *output, unsigned long frame_count,  
    const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags status_flags, void *user_data){

    // cast data passed through stream to our structure
    Sound::paTestData *data = (Sound::paTestData*) user_data;
    float *out = (float*)output;
    (void) input;
    (void) time_info;
    (void) status_flags;
    for (unsigned int i = 0; i < frame_count; i++) {
        out[i] = data->left_phase;
        out[i + 1] = data->right_phase;
        // generate simple sawtooth phaser that ranges between -1.0 and 1.0
        data->left_phase += 0.01f;
        // when the signal reaches top, drop back down
        if (data->left_phase >= 1.0f) {
            data->left_phase -= 2.0f;
        }
        // make the right phase have a higher pitch, so that we can distingish the left and 
        // right signals
        data->right_phase += 0.03f;
        if(data->right_phase >= 1.0f) {
            data->right_phase -= 2.0f;
        }
    }
    return 0;
}

Sound::Sound() {

}

Sound::~Sound() {

}

void Sound::init() {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Error initializing Portaudio" << std::endl;
        std::cerr << Pa_GetErrorText(err) << std::endl;
        exit(1);
    }

    size_t sample_rate = 44100;
    // Open an audio I/O stream 
    err = Pa_OpenDefaultStream(&stream, 
        0, // no input channels
        2, // stero output
        paFloat32, // 32 bit floating point output
        sample_rate, 
        256, // frames per buffer, i.e. the number of sample 
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
    PaError err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "Error with terminating PortAudio" << std::endl;
        std::cerr << Pa_GetErrorText(err) << std::endl;
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
