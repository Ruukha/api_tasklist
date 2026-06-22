#include <WiFi.h>
#include "wifiManager.h"
#include "credentials.h"
#include "config.h"

bool WifiManager::connect()
{
    objective = WL_CONNECTED;
    unsigned long now = millis();

    if (WiFi.status() == WL_CONNECTED){
        connecting = false;
        errorMessage = "";
        statusMessage = "WiFi connected!\n";
        return true;
    }
    else if (!connecting){
        WiFi.begin(Credentials::SSID, Credentials::password);
        connecting = true;
        startedConnection = now;
        errorMessage = "";
    }
    else if (now - startedConnection > Config::WIFI_TIMEOUT_MS){
        errorMessage = {"Unable to connect to wifi"};
        return false;
    }

    statusMessage = "Trying to connect to wifi... Status: " + String(WiFi.status());
    return false;
}

bool WifiManager::disconnect(){
    objective = WL_DISCONNECTED;
    statusMessage = {"Disconnecting wifi..."};
    connecting = false;
    return WiFi.disconnect(true);
}

void WifiManager::update(){
    unsigned long now = millis();
    if (now - lastAttempt < Config::WIFI_RETRY_MS){ return; }
    status = WiFi.status();
    if (status == objective){ return; }

    if (objective == WL_CONNECTED){
        connect();
    }
    else if (objective == WL_DISCONNECTED){
        disconnect();
    }
    else {
        errorMessage = "Objective status unknown: " + String(objective);
        return;
    }
    lastAttempt = now;
}

bool WifiManager::isConnected(){
    return (WiFi.status() == WL_CONNECTED);
}

bool WifiManager::hasError(){
    return !errorMessage.isEmpty();
}
