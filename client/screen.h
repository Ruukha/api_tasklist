#pragma once
#include <Arduino.h>
#include <Adafruit_ILI9341.h>

void test();
void screen_update();
void draw_task(String id, String name, Adafruit_ILI9341 tft);