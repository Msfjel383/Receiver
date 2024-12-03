/*
  RC_Receiver.h - Library for reading PWM value form an rc reciver
  Created by Nils Lahaye, 2022.
  Released into the public domain.
  Modified by MS for non-blocking execution, 2024
*/

#ifndef RC_Receiver_h
#define RC_Receiver_h

#include "Arduino.h"
#include <vector>

class RC_Receiver {
public:
    // Constructor: Accepts a vector of up to 8 channel pins
    RC_Receiver(const std::vector<uint8_t>& pins);

    // Set minimum and maximum values for each channel
    void setMinMax(int minMax[][2]);

    // Get raw PWM value from a channel (1-indexed)
    long getRaw(int channel);

    // Get mapped PWM value (0 to 100) from a channel (1-indexed)
    long getMap(int channel);

    void init(const std::vector<uint8_t>& pins); // Initialization

private:
    static void handleInterrupt0();
    static void handleInterrupt1();
    static void handleInterrupt2();
    static void handleInterrupt3();
    static void handleInterrupt4();
    static void handleInterrupt5();
    static void handleInterrupt6();
    static void handleInterrupt7();

    static RC_Receiver* instance;

    std::vector<uint8_t> _ch_pins; // Pins for channels
    int _minMax[8][2]; // Min-max values for mapping
    volatile unsigned long _pulseStartTime[8]; // Start times for pulses
    volatile unsigned long _pulseWidth[8]; // Pulse widths
    volatile bool _pulseComplete[8]; // Pulse completion flags
};

#endif