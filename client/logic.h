#pragma once
#include <Adafruit_ILI9341.h>

bool update(Adafruit_ILI9341 &tft, StaticJsonDocument<4096> &tasks, int counter=0, bool menu=0, int op=0);
void scroll(Adafruit_ILI9341 &tft, StaticJsonDocument<4096> &tasks, int counter);
bool getSlice(StaticJsonDocument<4096> &doc, StaticJsonDocument<2048>& outDoc, int start, int end);
const char* getId(StaticJsonDocument<4096> &tasks, int counter);
