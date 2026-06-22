#pragma once
#include <Arduino.h>

#include "initResult.h"

enum class ButtonState {
    NONE,
    PRESS,
    HOLD
};

class Button {
    private:
        const uint8_t pin;
        const unsigned long debounce_ms;
        const unsigned long hold_ms;

        unsigned long last_debounce;
        int raw_state;
        int debounced_state;
        int last_raw_state;
        int last_debounced_state;
        unsigned long hold_start;
        bool hold;
        bool hold_sent;
    
    public:
        Button(uint8_t pin, unsigned long debounce_ms, unsigned long hold_ms);
        InitResult begin();
        ButtonState read();
};