/*
  RC_Receiver.cpp - Library for reading PWM value form an rc reciver
  Created by Nils Lahaye, 2022.
  Released into the public domain.
  Modified by MS for non-blocking execution, 2024
*/

#include "RC_Receiver.h"

RC_Receiver* RC_Receiver::instance = nullptr;

// Constructor
RC_Receiver::RC_Receiver() {
    instance = this;
}
// Destructor
RC_Receiver::~RC_Receiver() {
    instance = nullptr;
    // Disable interrupts
    for(auto i : _ch_pins){
        gpio_intr_disable((gpio_num_t)i);
        gpio_set_intr_type((gpio_num_t)i, GPIO_INTR_DISABLE);
    }
}

// Initialization function
void RC_Receiver::init(std::vector<uint8_t> pins, std::vector<std::pair<uint16_t, uint16_t>> minMax) {
    // Set pins
    init(pins);
    // Set min-max values
    setMinMax(minMax);
}

void RC_Receiver::init(std::vector<uint8_t> pins) { 
    // Set pins
    _ch_pins = pins;
    uint8_t count = 0;
    for (auto i : pins){
        configure_gpio_with_interrupt(i, count);
        count++;
    }
}

// Set new min-max values
void RC_Receiver::setMinMax(std::vector<std::pair<uint16_t, uint16_t>> &minMax) {
    _minMax = minMax;
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
    return map(_pulseWidth[idx], _minMax[idx].first, _minMax[idx].second, 0, 1000);
}

// Interrupt handler
void IRAM_ATTR RC_Receiver::handleInterrupt(void* arg) {
    // Get the channel number from the argument
    uint8_t count = (uint8_t)(uintptr_t)arg;
    gpio_num_t pin = (gpio_num_t)instance->_ch_pins[count];
    if (gpio_get_level(pin) == HIGH) {
        instance->_pulseStartTime[count] = micros();
    } else {
        instance->_pulseWidth[count] = micros() - instance->_pulseStartTime[count];
    }
}
// Definition of the static variable to check if the ISR service is installed
bool RC_Receiver::is_isr_service_installed = false;

// Configure GPIO pin and interrupt
void RC_Receiver::configure_gpio_with_interrupt(uint8_t pin, uint8_t count)  {
    // GPIO-Konfiguration
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << ((gpio_num_t)pin)),  // Pin-Bitmaske
        .mode = GPIO_MODE_INPUT,       //Define as input
        .pull_up_en = GPIO_PULLUP_DISABLE,  // deaktivate pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // deaktivate pull-down
        .intr_type = GPIO_INTR_ANYEDGE // Interupt by any edge
    };
    // set GPIO with the configurations
    gpio_config(&io_conf);
    // install ISR service, if not already installed
    if (!is_isr_service_installed) {
        gpio_install_isr_service(0);
        is_isr_service_installed = true;
    }
    //  Add ISR handler
    gpio_isr_handler_add((gpio_num_t)pin, handleInterrupt, (void *)count);
}