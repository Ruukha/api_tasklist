#pragma once
#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "icons.h"
#include "initResult.h"

class Screen{
    private:
        Adafruit_ILI9341 tft;
        const uint8_t pin_cs;
        const uint8_t pin_rst;
        const uint8_t pin_dc;
        const uint8_t pin_sdi;
        const uint8_t pin_sck;
        const uint8_t pin_led;
    
    public:
        Screen(const uint8_t pin_cs, const uint8_t pin_rst, const uint8_t pin_dc, const uint8_t pin_sdi, const uint8_t pin_sck, const uint8_t pin_led); 
        InitResult begin(); 
        int16_t getHeight() const;
        int16_t getWidth() const;
        void setBrightness(uint8_t brightness);
        void println(const String &text);
        void clear();
        void drawIcon(const Icon& icon, const uint8_t frame, const int x0, const int y0);
        void setTextSize(uint8_t size);
};