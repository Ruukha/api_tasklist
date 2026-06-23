#pragma once

#include "screen.h"
#include "wifiManager.h"
#include "lightSensor.h"

enum PowerState{
    ACTIVE,
    SCREEN_OFF,
    SLEEP,
    DEEP_SLEEP
};

PowerState update(const unsigned long &now, const unsigned long &lastActivity);
bool wifiConnect(const char* &SSID, const char* &password);

class PowerManager{
    private:
        PowerState lastState{ACTIVE};
        unsigned long lastActivity{0};
        Screen& screen;
        WifiManager& wifi;
        LightSensor& lightSensor;
    
    public:
        PowerManager(Screen& screen, WifiManager& wifi, LightSensor& lightSensor);
        void update();
        void activity();
};