#pragma once

enum PowerState{
    ACTIVE,
    SCREEN_OFF,
    SLEEP,
    DEEP_SLEEP
};

PowerState update(const unsigned long &now, const unsigned long &lastActivity);
bool wifiConnect(const char* &SSID, const char* &password);