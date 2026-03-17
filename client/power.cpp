#include <WiFi.h>
#include "power.h"
#include "config.h"

PowerState update(const unsigned long &now, const unsigned long &lastActivity)
{
    unsigned long difference = now - lastActivity;
    if (difference < TIMEOUT_MS) return ACTIVE;
    if (difference >= SLEEP_MS) return SLEEP;
    return SCREEN_OFF;
}

bool wifiConnect(const char *&SSID, const char *&password)
{
    WiFi.begin(SSID, password);

    unsigned long start = millis();
    while(WiFi.status() != WL_CONNECTED && millis() - start < WIFI_MS){
        delay(100);
    }

    if (WiFi.status() == WL_CONNECTED){
        Serial.print("WiFi connected!\n");
        return true;
    }
    Serial.printf("Wifi not connected. Status: %d\n", WiFi.status());
    return false;
}