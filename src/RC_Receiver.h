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
#include "driver/gpio.h"

class RC_Receiver {
public:
    // Constructor:
    RC_Receiver();
    // Destructor:
    ~RC_Receiver();

    // Initialization
    void init(std::vector<uint8_t> pins);
    void init(std::vector<uint8_t> pins, int minMax[8][2]);
    
    // Set minimum and maximum values for each channel
    void setMinMax(int minMax[][2]);

    // Get raw PWM value from a channel
    long getRaw(int channel);

    // Get mapped PWM value (0 to 100) from a channel
    long getMap(int channel);

private:
    static void handleInterrupt(void* arg);
    //set the GPIO pin to input mode and enable interrupt
    void configure_gpio_with_interrupt(uint8_t pin, uint8_t count);
    //pointer to the instance of the class
    static RC_Receiver* instance;

    std::vector<uint8_t> _ch_pins; // Pins for channels
    int _minMax[8][2]; // Min-max values for mapping
    volatile unsigned long _pulseStartTime[8]; // Start times for pulses
    volatile unsigned long _pulseWidth[8]; // Pulse widths
};

#endif