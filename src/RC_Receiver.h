#ifndef RC_Receiver_h
#define RC_Receiver_h

#include "Arduino.h"

#define minMaxLength 2
#define MAX_CHANNELS 8

class RC_Receiver {
public:
    RC_Receiver(std::initializer_list<uint8_t> channels); // Constructor for 1-8 channels
    void setMinMax(int minMax[][minMaxLength]);          // Set Min/Max values
    long getRaw(int ch);                                 // Return raw pulse width
    long getMap(int ch);                                 // Return mapped value (0 to 100)

private:
    static RC_Receiver* instance;                       // Global instance pointer
    static void handleInterrupt0();
    static void handleInterrupt1();
    static void handleInterrupt2();
    static void handleInterrupt3();
    static void handleInterrupt4();
    static void handleInterrupt5();
    static void handleInterrupt6();
    static void handleInterrupt7();

    void handleInterrupt(uint8_t channel);

    uint8_t _ch_pin[MAX_CHANNELS] = {0};                 // Input pins (0 means unused)
    int _minMax[MAX_CHANNELS][minMaxLength];             // Min/Max mapping values
    volatile unsigned long pulseStartTime[MAX_CHANNELS] = {0};
    volatile unsigned long pulseWidth[MAX_CHANNELS] = {0};
    volatile bool pulseComplete[MAX_CHANNELS] = {false};
    uint8_t _numChannels = 0;                            // Number of channels used
};

#endif