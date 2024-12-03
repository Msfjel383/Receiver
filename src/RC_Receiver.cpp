/*
  RC_Receiver.cpp - Library for reading PWM value form an rc reciver
  Created by Nils Lahaye, 2022.
  Released into the public domain.
  Modified by MS for non-blocking execution, 2024
*/

#include "RC_Receiver.h"

RC_Receiver* RC_Receiver::instance = nullptr;

// Constructor: Initialize with given pins
RC_Receiver::RC_Receiver(const std::vector<uint8_t>& pins) {
    instance = this;
}

// Initialization function
void RC_Receiver::init(const std::vector<uint8_t>& pins) {
    _ch_pins = pins;

    // Default min-max values
    for (int i = 0; i < 8; ++i) {
        _minMax[i][0] = 500;
        _minMax[i][1] = 2500;
        _pulseStartTime[i] = 0;
        _pulseWidth[i] = 0;
        _pulseComplete[i] = false;
    }

    // Set pins as input and attach interrupts
        if (_ch_pins[0] != 0) {
            pinMode(_ch_pins[0], INPUT);
            attachInterrupt(digitalPinToInterrupt(_ch_pins[0]), handleInterrupt0, CHANGE);
        }
        if (_ch_pins[1] != 0) {
            pinMode(_ch_pins[1], INPUT);
            attachInterrupt(digitalPinToInterrupt(_ch_pins[1]), handleInterrupt1, CHANGE);
        }
        if (_ch_pins[2] != 0) {
            pinMode(_ch_pins[2], INPUT);
            attachInterrupt(digitalPinToInterrupt(_ch_pins[2]), handleInterrupt2, CHANGE);
        }
        if (_ch_pins[3] != 0) {
            pinMode(_ch_pins[3], INPUT);
            attachInterrupt(digitalPinToInterrupt(_ch_pins[3]), handleInterrupt3, CHANGE);
        }
        if (_ch_pins[4] != 0) {
            pinMode(_ch_pins[4], INPUT);
            attachInterrupt(digitalPinToInterrupt(_ch_pins[4]), handleInterrupt4, CHANGE);
        }
        if (_ch_pins[5] != 0) {
            pinMode(_ch_pins[5], INPUT);
            attachInterrupt(digitalPinToInterrupt(_ch_pins[5]), handleInterrupt5, CHANGE);
        }
        if (_ch_pins[6] != 0) {
            pinMode(_ch_pins[6], INPUT);
            attachInterrupt(digitalPinToInterrupt(_ch_pins[6]), handleInterrupt6, CHANGE);
        }
        if (_ch_pins[7] != 0) {
            pinMode(_ch_pins[7], INPUT);
            attachInterrupt(digitalPinToInterrupt(_ch_pins[7]), handleInterrupt7, CHANGE);
        }
    
}

// Set new min-max values
void RC_Receiver::setMinMax(int minMax[][2]) {
    for (int i = 0; i < 8; ++i) {
        _minMax[i][0] = minMax[i][0];
        _minMax[i][1] = minMax[i][1];
    }
}

// Get raw PWM value
long RC_Receiver::getRaw(int channel) {
    if (channel < 1 || channel > (int)_ch_pins.size()) return 0; // Validate channel
    return _pulseWidth[channel - 1];
}

// Get mapped PWM value
long RC_Receiver::getMap(int channel) {
    if (channel < 1 || channel > (int)_ch_pins.size()) return 0; // Validate channel
    int idx = channel - 1;
    return map(_pulseWidth[idx], _minMax[idx][0], _minMax[idx][1], 0, 100);
}

// Interrupt handler
void RC_Receiver::handleInterrupt0() {
    if (digitalRead(instance->_ch_pins[0]) == HIGH) {
        instance->_pulseStartTime[0] = micros();
    } else {
        instance->_pulseWidth[0] = micros() - instance->_pulseStartTime[0];
        instance->_pulseComplete[0] = true;
    }
}

void RC_Receiver::handleInterrupt1() {
    if (digitalRead(instance->_ch_pins[1]) == HIGH) {
        instance->_pulseStartTime[1] = micros();
    } else {
        instance->_pulseWidth[1] = micros() - instance->_pulseStartTime[1];
        instance->_pulseComplete[1] = true;
    }
}

void RC_Receiver::handleInterrupt2() {
    if (digitalRead(instance->_ch_pins[2]) == HIGH) {
        instance->_pulseStartTime[2] = micros();
    } else {
        instance->_pulseWidth[2] = micros() - instance->_pulseStartTime[2];
        instance->_pulseComplete[2] = true;
    }
}

void RC_Receiver::handleInterrupt3() {
    if (digitalRead(instance->_ch_pins[3]) == HIGH) {
        instance->_pulseStartTime[3] = micros();
    } else {
        instance->_pulseWidth[3] = micros() - instance->_pulseStartTime[3];
        instance->_pulseComplete[3] = true;
    }
}

void RC_Receiver::handleInterrupt4() {
    if (digitalRead(instance->_ch_pins[4]) == HIGH) {
        instance->_pulseStartTime[4] = micros();
    } else {
        instance->_pulseWidth[4] = micros() - instance->_pulseStartTime[4];
        instance->_pulseComplete[4] = true;
    }
}

void RC_Receiver::handleInterrupt5() {
    if (digitalRead(instance->_ch_pins[5]) == HIGH) {
        instance->_pulseStartTime[5] = micros();
    } else {
        instance->_pulseWidth[5] = micros() - instance->_pulseStartTime[5];
        instance->_pulseComplete[5] = true;
    }
}

void RC_Receiver::handleInterrupt6() {
    if (digitalRead(instance->_ch_pins[6]) == HIGH) {
        instance->_pulseStartTime[6] = micros();
    } else {
        instance->_pulseWidth[6] = micros() - instance->_pulseStartTime[6];
        instance->_pulseComplete[6] = true;
    }
}

void RC_Receiver::handleInterrupt7() {
    if (digitalRead(instance->_ch_pins[7]) == HIGH) {
        instance->_pulseStartTime[7] = micros();
    } else {
        instance->_pulseWidth[7] = micros() - instance->_pulseStartTime[7];
        instance->_pulseComplete[7] = true;
    }
}