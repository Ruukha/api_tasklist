#include "button.h"

Button::Button(uint8_t pin, unsigned long debounce_ms, unsigned long hold_ms)
    : pin(pin),
    debounce_ms(debounce_ms),
    hold_ms(hold_ms),
    last_debounce(0),
    raw_state(HIGH),
    debounced_state(HIGH),
    last_raw_state(HIGH),
    last_debounced_state(HIGH),
    hold_start(0),
    hold(false),
    hold_sent(false)
{}

InitResult Button::begin(){
    pinMode(pin, INPUT_PULLUP);
    digitalWrite(pin, HIGH);

    return {InitStatus::OK, "Button"};
}

ButtonState Button::read()
{
    const unsigned long now = millis();

    //debouncing
    raw_state = digitalRead(pin);
    if (raw_state != last_raw_state){
        last_debounce = now;
    }
    last_raw_state = raw_state;
    
    if ((now - last_debounce) > debounce_ms){
        last_debounced_state = debounced_state;
        debounced_state = raw_state;

        if (debounced_state != last_debounced_state){
            //Falling edge
            if (debounced_state == LOW){
                hold_start = now;
                hold = true;
            }

            //Rising edge
            else if (debounced_state == HIGH){
                hold = false;
                if (hold_sent){
                    hold_sent = false;
                    return ButtonState::NONE;    
                }
                return ButtonState::PRESS;
            }
        }
        if (!hold_sent && hold && (now - hold_start) >= hold_ms){
            hold_start = now;
            hold_sent = true;
            return ButtonState::HOLD;
        }
    }

    return ButtonState::NONE;
}
