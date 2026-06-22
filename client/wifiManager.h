#pragma once
#include <Arduino.h>

class WifiManager{
    private:
        unsigned long lastAttempt{0};
        wl_status_t objective{WL_CONNECTED};
        wl_status_t status{WL_DISCONNECTED};
        bool connecting{false};
        unsigned long startedConnection{0};
        String errorMessage{""};
        String statusMessage{""};

    public:
        bool connect();
        bool disconnect();
        void update();
        bool isConnected();
        bool hasError();
};