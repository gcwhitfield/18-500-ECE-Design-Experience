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
        hits.resize(4)
    }
}

DrumPeripheral::~DrumPeripheral() {
    if (serial.isDeviceOpen()) {
        serial.closeDevice();
    }
}

void DrumPeripheral::update(float elapsed) {
    (void) elapsed;
    char c;
    int size = serial.available();
    if (size > 0) {
        while (size > 0) {
            if (serial.readChar(&c)) { // if we receive more than 1 message in a single frame, then 
            // only accept data from the LAST message received
                std::cout << c;
            }
            size--;
        }
        
        // if the char is an acceptable input
        for (auto i = acceptable_inputs.begin(); i != acceptable_inputs.end(); i++) {
            if (c == *i) {
                if (c & HitLocation::DRUM_0) {

                } else if (c & HitLocation::DRUM_1) {

                } else if (c & HitLocation::DRUM_2) {
                    
                } else if (c & HitLocation::DRUM_3) {

                }
                // TODO: call Mode::handle_drum_wrapper based on input 
            }
        }

        std::cout << std::endl;

        serial.flushReceiver();
    }
}
