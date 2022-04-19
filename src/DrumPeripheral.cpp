#include "DrumPeripheral.hpp"

// code for reading serial taken from 'serialib' example 
//https://github.com/imabot2/serialib/blob/master/example1/main.cpp
DrumPeripheral::DrumPeripheral() {
    // initialize connection to serial 
    {
        std::string serial_port("/dev/cu.SLAB_USBtoUART");
        // connection to the serial port
        char error_opening = serial.openDevice(serial_port.c_str(), 115200);

        // if connection fails, return the error code. Otherwise, display a success message
        if (error_opening != 1) {
            std::cerr << "Error opening serial port for drum peripheral " << serial_port << std::endl;
            return;
        }
        std::cout << "Connection to drum peripheral successful!" << std::endl;
        serial.flushReceiver();
    }

    // initialize 'hits'
    {
        hits.resize(4);
    }

    // initialize acceptable inputs
    {
        acceptable_inputs.push_back(0);
        acceptable_inputs.push_back(1);
        acceptable_inputs.push_back(2);
        acceptable_inputs.push_back(3);
        acceptable_inputs.push_back(4);
        acceptable_inputs.push_back(5);
        acceptable_inputs.push_back(6);
        acceptable_inputs.push_back(7);
        acceptable_inputs.push_back(8);
        acceptable_inputs.push_back(9);
        acceptable_inputs.push_back(10);
        acceptable_inputs.push_back(11);
        acceptable_inputs.push_back(12);
        acceptable_inputs.push_back(13);
        acceptable_inputs.push_back(14);
        acceptable_inputs.push_back(15);
    }

    // for (size_t i = 0; i < acceptable_inputs.size(); i++) {
    //     std::cout << acceptable_inputs[i] << std::endl;
    // }
    // for (size_t i = 0; i < acceptable_inputs.size(); i++) {
    //     std::cout << acceptable_inputs[i] + '0' << std::endl;
    // }
    // exit(1);
}

DrumPeripheral::~DrumPeripheral() {
    if (serial.isDeviceOpen()) {
        serial.closeDevice();
    }
}

void DrumPeripheral::update(float elapsed) {
    (void) elapsed;

    // don't do anything if there aren't any drums connected to the game
    if (!serial.isDeviceOpen()) {
        return;
    }

    char c;
    int size = serial.available();
    std::cout << (int)hits[0] << " : " << (int)hits[1] << " : " << (int)hits[2] << " : " << (int)hits[3] << std::endl;
    if (size <= 0) {
        hits[0] = (char)HitInfo::NONE;
        hits[1] = (char)HitInfo::NONE;
        hits[2] = (char)HitInfo::NONE;
        hits[3] = (char)HitInfo::NONE;
    } else {
        while (size > 0) {
            
            if (serial.readChar(&c)) { // if we receive more than 1 message in a single frame, then 

            }
            size--;
        }
        // if the char is an acceptable input
        for (size_t i = 0; i < acceptable_inputs.size(); i++) {
            if (c == acceptable_inputs[i] + '0') {
                if (c & HitLocation::DRUM_0) {
                    if ((HitInfo)hits[0] == HitInfo::NONE)
                    {
                        hits[0] = (char)HitInfo::PRESS;
                    } else if ((HitInfo)hits[0] == HitInfo::PRESS) {
                        hits[0] = (char)HitInfo::HOLD;
                    }
                } else {
                    hits[0] = (char)HitInfo::NONE;
                } 

                if (c & HitLocation::DRUM_1) {
                    if ((HitInfo)hits[1] == HitInfo::NONE)
                    {
                        hits[1] = (char)HitInfo::PRESS;
                    } else if ((HitInfo)hits[1] == HitInfo::PRESS) {
                        hits[1] = (char)HitInfo::HOLD;
                    }
                } else {
                    hits[1] = (char)HitInfo::NONE;
                }

                if (c & HitLocation::DRUM_2) {
                    if ((HitInfo)hits[2] == HitInfo::NONE)
                    {
                        hits[2] = (char)HitInfo::PRESS;
                    } else if ((HitInfo)hits[2] == HitInfo::PRESS) {
                        hits[2] = (char)HitInfo::HOLD;
                    }
                } else {
                    hits[2] = (char)HitInfo::NONE;
                }
                
                if (c & HitLocation::DRUM_3) {
                    if ((HitInfo)hits[3] == HitInfo::NONE)
                    {
                        hits[3] = (char)HitInfo::PRESS;
                    } else if ((HitInfo)hits[3] == HitInfo::PRESS) {
                        hits[3] = (char)HitInfo::HOLD;
                    }
                } else {
                    hits[3] = (char)HitInfo::NONE;
                }
                
                // TODO: call Mode::handle_drum_wrapper based on input 
                Mode::handle_drum_wrapper(hits);
                break;
            }
        }
        
    }
    // empty the serial buffer at the end of each frame
    serial.flushReceiver();
    
}