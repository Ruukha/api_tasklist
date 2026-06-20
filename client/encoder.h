#pragma once
#include <ESP32Encoder.h>

enum Direction{
    CCW = -1,
    None = 0,
    CW = 1
};

class Encoder{
    private:
        uint8_t pin_dt;
        uint8_t pin_clk;
        int64_t lastCount;
        ESP32Encoder enc;

    public:
        Encoder(uint8_t pin_dt, uint8_t pin_clk);
        bool begin();
        Direction read();
};