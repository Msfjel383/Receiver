/*
  RC_Receiver.cpp - Library for reading PWM value form an rc reciver
  Created by Nils Lahaye, 2022.
  Released into the public domain.
  Modified by MS for non-blocking execution, 2024
*/

#include "RC_Receiver.h"

// Define the static instance pointer
RC_Receiver* RC_Receiver::instance = nullptr;

RC_Receiver::RC_Receiver(std::initializer_list<uint8_t> channels) {
    instance = this; // Set the static instance pointer

    _numChannels = channels.size();
    uint8_t idx = 0;

    // Initialize channels and attach interrupts for non-zero pins
    for (uint8_t pin : channels) {
        if (idx >= MAX_CHANNELS) break;

        _ch_pin[idx] = pin;
        if (pin != 0) {
            pinMode(pin, INPUT);
            switch (idx) {
                case 0: attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt0, CHANGE); break;
                case 1: attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt1, CHANGE); break;
                case 2: attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt2, CHANGE); break;
                case 3: attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt3, CHANGE); break;
                case 4: attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt4, CHANGE); break;
                case 5: attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt5, CHANGE); break;
                case 6: attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt6, CHANGE); break;
                case 7: attachInterrupt(digitalPinToInterrupt(pin), handleInterrupt7, CHANGE); break;
            }
        }
        idx++;
    }

    // Initialize default Min/Max values
    for (int i = 0; i < MAX_CHANNELS; i++) {
        _minMax[i][0] = 1010;
        _minMax[i][1] = 2020;
    }
}

void RC_Receiver::setMinMax(int minMax[][minMaxLength]) {
    for (int i = 0; i < _numChannels; i++) {
        _minMax[i][0] = minMax[i][0];
        _minMax[i][1] = minMax[i][1];
    }
}

long RC_Receiver::getRaw(int ch) {
    if (ch < 1 || ch > _numChannels) return -1; // Invalid channel
    return pulseWidth[ch - 1];
}

long RC_Receiver::getMap(int ch) {
    if (ch < 1 || ch > _numChannels) return -1; // Invalid channel
    int idx = ch - 1;
    return map(pulseWidth[idx], _minMax[idx][0], _minMax[idx][1], 0, 100);
}

// Static interrupt handlers
void RC_Receiver::handleInterrupt0() { instance->handleInterrupt(0); }
void RC_Receiver::handleInterrupt1() { instance->handleInterrupt(1); }
void RC_Receiver::handleInterrupt2() { instance->handleInterrupt(2); }
void RC_Receiver::handleInterrupt3() { instance->handleInterrupt(3); }
void RC_Receiver::handleInterrupt4() { instance->handleInterrupt(4); }
void RC_Receiver::handleInterrupt5() { instance->handleInterrupt(5); }
void RC_Receiver::handleInterrupt6() { instance->handleInterrupt(6); }
void RC_Receiver::handleInterrupt7() { instance->handleInterrupt(7); }

void RC_Receiver::handleInterrupt(uint8_t channel) {
    if (digitalRead(_ch_pin[channel]) == HIGH) {
        pulseStartTime[channel] = micros();
    } else {
        pulseWidth[channel] = micros() - pulseStartTime[channel];
        pulseComplete[channel] = true;
    }
}