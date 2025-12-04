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

    static unsigned long last_debounce;
    static int raw_state;
    static int debounced_state;
    static int last_raw_state;
    static int last_debounced_state;
    static unsigned long ms;
    static unsigned long hold_start;
    static bool hold;
};

void init(Button &btn);
ButtonState update(Button &btn);