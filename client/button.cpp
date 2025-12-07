#include "button.h"

void init(Button &btn)
{
    btn.last_debounce = 0;
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
    const unsigned long now = millis();

    //debouncing
    btn.raw_state = digitalRead(btn.pin);
    if (btn.raw_state != btn.last_raw_state){
        btn.last_debounce = now;
    }
    btn.last_raw_state = btn.raw_state;
    
    if ((now - btn.last_debounce) > btn.debounce_ms){
        btn.last_debounced_state = btn.debounced_state;
        btn.debounced_state = btn.raw_state;

        if (btn.debounced_state != btn.last_debounced_state){
            //Falling edge
            if (btn.debounced_state == LOW){
                btn.hold_start = now;
                btn.hold = true;
            }

            //Rising edge
            else if (btn.debounced_state == HIGH){
                btn.hold = false;
                return BUTTON_PRESS;
            }
        }
        if (btn.hold && (now - btn.hold_start) >= btn.hold_ms){
            return BUTTON_HOLD;
        }
    }

    return BUTTON_NONE;
}
