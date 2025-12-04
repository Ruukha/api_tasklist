#include "button.h"

void init(Button &btn)
{
    btn.last_debounced_state = 0;
    btn.raw_state = HIGH;
    btn.debounced_state = HIGH;
    btn.last_raw_state = HIGH;
    btn.last_debounced_state = HIGH;
    btn.ms = 0;
    btn.hold_start = 0;
    btn.hold = false;
}

ButtonState update(Button &btn)
{
    //debouncing
    btn.raw_state = digitalRead(btn.pin);
    if (btn.raw_state != btn.last_raw_state){
        btn.debounced_state = btn.raw_state;
        btn.last_debounced_state = millis();
    }
    btn.last_raw_state = btn.raw_state;

    if ((millis() - btn.last_debounced_state) > btn.debounce_ms){
        //Falling edge
        if (btn.raw_state == LOW && btn.last_debounced_state == HIGH){
        btn.hold_start = millis();
        btn.hold = true;
        }
        else if (btn.hold && millis() - btn.hold_start >= btn.hold_ms){
        return BUTTON_HOLD;
        }
        //Rising edge
        else if (btn.raw_state == HIGH && btn.last_debounced_state == LOW){
        btn.hold = false;
        return BUTTON_PRESS;
        }
        btn.last_debounced_state = btn.debounced_state;
    }
}
