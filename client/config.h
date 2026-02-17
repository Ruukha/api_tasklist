#pragma once
#include <Arduino.h>

//user variables
extern const char* SSID; //Wifi name
extern const char* password; //Wifi password
extern const int TEXT_SIZE;
extern const int HOLD_MS;

//server variables
extern const char* IP; //server IP

//other variables
extern const int DEBOUNCE_MS;
extern const int DELAY_MS;
extern const int FRAME_MS;
extern int tasks_cap;
