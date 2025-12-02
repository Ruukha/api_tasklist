#pragma once
#include <Arduino.h>
#include <Adafruit_ILI9341.h>

void test(Adafruit_ILI9341 &tft);
void screen_update();
void draw_task(String &id, String &name, Adafruit_ILI9341 &tft);
void init_screen(Adafruit_ILI9341 &tft);