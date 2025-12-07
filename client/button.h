#pragma once
#include <Arduino.h>

enum ButtonState {
    BUTTON_NONE,
    BUTTON_PRESS,
    BUTTON_HOLD
};

struct Button {
    const uint8_t pin;
    const unsigned long debounce_ms;
    const unsigned long hold_ms;

    unsigned long last_debounce;
    int raw_state;
    int debounced_state;
    int last_raw_state;
    int last_debounced_state;
    unsigned long ms;
    unsigned long hold_start;
    bool hold;
};

void init(Button &btn);
ButtonState update(Button &btn);