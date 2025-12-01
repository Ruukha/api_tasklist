#pragma once
#include <Arduino.h>

//user variable definitions
const char* SSID = ""; //Wifi name
const char* password = ""; //Wifi password
int TEXT_SIZE = 3;

//server variable definitions
const String BASE = "http://127.0.0.1"; //server IP
const String PORT = "5000";
const String IP = BASE + ":" + PORT;

//pin definitions
constexpr int TFT_CS = 5;
constexpr int TFT_RST = 4;
constexpr int TFT_DC = 17;
constexpr int TFT_SDI = 23;
constexpr int TFT_SCK = 18;
constexpr int TFT_LED = 2;
constexpr int BTN = 32;
constexpr int DEBOUNCE_MS = 50;

//code utilities definitions
const int DELAY = 60000; //measured in ms
time_t last_update;
time_t last_cached_update;