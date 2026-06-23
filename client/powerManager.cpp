#include <WiFi.h>
#include "powerManager.h"
#include "config.h"

PowerState update(const unsigned long &now, const unsigned long &lastActivity)
{
    unsigned long difference = now - lastActivity;
    if (difference < Config::TIMEOUT_MS) return ACTIVE;
    if (difference >= Config::SLEEP_MS) return SLEEP;
    return SCREEN_OFF;
}

PowerManager::PowerManager(Screen& screen, WifiManager& wifi, LightSensor& lightSensor)
    : screen(screen),
    wifi(wifi),
    lightSensor(lightSensor)
{}

void PowerManager::update(){
    PowerState state;
    unsigned long now = millis();
    unsigned long difference = now - lastActivity;
    if (difference < Config::TIMEOUT_MS) state = ACTIVE;
    else if (difference >= Config::SLEEP_MS) state = SLEEP;
    else state = SCREEN_OFF;

    if (state != lastState){
        switch(state){
            case ACTIVE:
                Serial.println("Turning on...");
                // showIcon = true;
                screen.setBrightness(lightSensor.read());
                setCpuFrequencyMhz(160);
                if (lastState == SLEEP){
                    wifi.connect();
                    // counter = 0;
                }
                lastActivity = now;
                // showIcon = false;
                break;
            case SCREEN_OFF:
                Serial.println("Turning screen off...");
                setCpuFrequencyMhz(80);
                screen.setBrightness(0);
                break;
            case SLEEP:
                Serial.println("Going to sleep...");
                wifi.disconnect();
                setCpuFrequencyMhz(80);
                break;
        }
        lastState = state;
    }
}

void PowerManager::activity()
{
    lastActivity = millis();
}
