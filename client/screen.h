#pragma once
#include <Arduino.h>
#include <Adafruit_ILI9341.h>

struct Screen {
    const uint8_t pin_cs;
    const uint8_t pin_dt;
    const uint8_t pin_rst;
    const uint8_t text_size;

    Adafruit_ILI9341 tft;
};

void test(Adafruit_ILI9341 &tft);
void update_screen();
void draw_task(String &id, String &name, Adafruit_ILI9341 &tft, const int selected = -1);
void init_screen(Adafruit_ILI9341 &tft);