#pragma once
#include <Adafruit_ILI9341.h>

void update(Adafruit_ILI9341 &tft, StaticJsonDocument<4096> &tasks, int counter);
void scroll(Adafruit_ILI9341 &tft, StaticJsonDocument<4096> &tasks, int counter);
bool getSlice(StaticJsonDocument<4096> &doc, StaticJsonDocument<2048>& outDoc, int start, int end);
const char* getId(StaticJsonDocument<4096> &tasks, int counter);
bool getPayload(StaticJsonDocument<4096> &);
void get_last_update();