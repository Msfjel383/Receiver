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

    //initialize the receiver with the pins for each channel and the min max values
    void init(std::vector<uint8_t> pins);
    void init(std::vector<uint8_t> pins, std::vector<std::pair<uint16_t, uint16_t>> minMax);
    
    // Set minimum and maximum values for each channel
    void setMinMax(std::vector<std::pair<uint16_t, uint16_t>> &minMax);

    // Get raw PWM value from a channel
    long getRaw(int channel);

    // Get mapped PWM value (0 to 1000) from a channel
    long getMap(int channel);

private:
    static bool is_isr_service_installed; // Flag to check if ISR service is installed
    static void handleInterrupt(void* arg);
    //set the GPIO pin to input mode and enable interrupt
    void configure_gpio_with_interrupt(uint8_t pin, uint8_t count);
    //pointer to the instance of the class
    static RC_Receiver* instance;

    std::vector<uint8_t> _ch_pins; // Pins for channels
    std::vector<std::pair<uint16_t, uint16_t>> _minMax; // Min-max values for mapping
    volatile unsigned long _pulseStartTime[20]; // Start times for pulses
    volatile unsigned long _pulseWidth[20]; // Pulse widths
};

#endif