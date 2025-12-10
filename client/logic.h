#pragma once
#include <Adafruit_ILI9341.h>

void update_logic(Adafruit_ILI9341 &tft, const int selected = -1);
void get_last_update();