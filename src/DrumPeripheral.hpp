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
        NONE = -1, // the drum is not currently being hit
        PRESS = 0, // for the first frame that the user holds the button down
        HOLD = 1 // for every subsequent frame where the user holds the button down
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
    std::vector<char> acceptable_inputs = {
            0x01, // [_ _ _ X]
            0x02, // [_ _ X _]
            0x03, // [_ _ X X]
            0x04, // [_ X _ _]
            0x05, // [_ X _ X]
            0x06, // [_ X X _]
            0x07, // [_ X X X]
            0x08, // [X _ _ _]
            0x09, // [X _ _ X]
            0x0A, // [X _ X _]
            0x0B, // [X _ X X]
            0x0C, // [X X _ _]
            0x0D, // [X X _ X]
            0x0E, // [X X X _]
            0x0F  // [X X X X]
        };

    std::vector<HitInfo> hits; 

    void update(float elapsed); // called every frame. Processes input from the drum peripheral, calls 
    // the drum callback function

    serialib serial;
};

#endif