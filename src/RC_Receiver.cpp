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
    //gpio_intr_disable(GPIO_NUM_4); // Disable interrupts for GPIO 4
}

// Initialization function
void RC_Receiver::init(std::vector<uint8_t> pins, int minMax[8][2]) {
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


// Funktion zur Konfiguration des GPIO-Pins
void RC_Receiver::configure_gpio_with_interrupt(uint8_t pin, uint8_t count)  {
    // GPIO-Pin konfigurieren
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << ((gpio_num_t)pin)),  // Pin festlegen
        .mode = GPIO_MODE_INPUT,       // Als Eingabe konfigurieren
        .pull_up_en = GPIO_PULLUP_DISABLE,  // Pull-Up deaktivieren
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // Pull-Down deaktivieren
        .intr_type = GPIO_INTR_ANYEDGE // Interrupt bei jeder Flanke
    };

    // Konfiguration anwenden
    gpio_config(&io_conf);

    // ISR-Service installieren (einmalig aufrufen, falls nicht schon geschehen)
    gpio_install_isr_service(0);

    // ISR-Handler für diesen GPIO-Pin hinzufügen
    gpio_isr_handler_add((gpio_num_t)pin, handleInterrupt, (void *)count);
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
void IRAM_ATTR RC_Receiver::handleInterrupt(void* arg) {
    // Pointer in uint8_t-Typ umwandeln
    uint8_t count = (uint8_t)(uintptr_t)arg;
    gpio_num_t pin = (gpio_num_t)instance->_ch_pins[count];
    if (gpio_get_level(pin) == HIGH) {
        instance->_pulseStartTime[count] = micros();
    } else {
        instance->_pulseWidth[count] = micros() - instance->_pulseStartTime[count];
    }
}