#pragma once
#include <Arduino.h>
#include <Adafruit_ILI9341.h>

void test(Adafruit_ILI9341 &tft);
void show_menu(Adafruit_ILI9341 &tft, StaticJsonDocument<1024> &task, int op=0);
void draw_task(String &id, String &name, Adafruit_ILI9341 &tft);
void draw_tasks(Adafruit_ILI9341 &tft, StaticJsonDocument<2048> &doc);
void init_screen(Adafruit_ILI9341 &tft);