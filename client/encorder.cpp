#include <ESP32Encoder.h>

#include "encoder.h"

Encoder::Encoder(uint8_t pin_dt, uint8_t pin_clk)
    : pin_dt(pin_dt),
    pin_clk(pin_clk),
    lastCount(0)
{}

bool Encoder::begin(){
    enc.attachHalfQuad(pin_dt, pin_clk);
    enc.setFilter(1023);
    enc.clearCount();

    return true;
}

Direction Encoder::read(){
    int64_t now = enc.getCount();
    int64_t delta = now - lastCount;
    if (delta == 0) return None;

    lastCount = now;
    return (delta > 0) ? CW : CCW;
}