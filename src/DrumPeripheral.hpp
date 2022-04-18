#ifndef DRUM_PERIPHERAL
#define DRUM_PERIPHERAL

#include "Beatmap.hpp"
#include "Mode.hpp"

#include <serialib.h>

#include <string>
#include <iostream>
#include <map>
#include <vector>

struct DrumPeripheral {
    DrumPeripheral();
    ~DrumPeripheral();

    enum HitInfo {
        NONE = 0, // the drum is not currently being hit
        PRESS = 1, // for the first frame that the user holds the button down
        HOLD = 2 // for every subsequent frame where the user holds the button down
    };

    enum HitLocation {
        DRUM_0 = 0x01,
        DRUM_1 = 0x02, 
        DRUM_2 = 0x04, 
        DRUM_3 = 0x08
    };

    // This is all of the valid inputs that the drum module can send to the computer via serial
    // The least significant bit is the right_most drum module, and then each subsequent bit 
    // corresponds to the next left drum. For example:
    // 
    // [ ] [ ] [ ] [X] <---- bit 0 (the LSB) corresponds to the right-most drum
    // [ ] [ ] [X] [ ] <---- bit 1 corresponds to the middle right drum
    // [ ] [X] [ ] [ ] <---- bit 2 corresponds to the middle left drum
    // [X] [ ] [ ] [ ] <---- bit 3 corresponds to the left-most drum
    //
    // The X in an entry of 'acceptable_inputs' means that the drum has been hit 
    std::vector<char> acceptable_inputs;

    std::vector<char> hits; 

    void update(float elapsed); // called every frame. Processes input from the drum peripheral, calls 
    // the drum callback function

    serialib serial;
};

#endif