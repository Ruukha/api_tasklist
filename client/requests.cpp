#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"

extern bool showIcon;

bool getPayload(StaticJsonDocument<4096> &doc){
    showIcon = true;
    try{
        HTTPClient http;
        http.begin(String(IP) + "/tasks");
        int code = http.GET();
        Serial.printf("HTTP status code: %d\n", code);

        if (code == 200){
            String payload = http.getString();
            http.end(); 
            DeserializationError error = deserializeJson(doc, payload);
            if (error) {
                Serial.printf("JSON parse failed!: %s\n", error);
                return false;
            }
            showIcon = false;
            return true;
        }
        else{
            http.end();
            return false;
        }
    }
    catch (...){
        return false;
    }
}

void get_last_update(time_t &last_update){
    showIcon = true;
    try{
        HTTPClient http;
        http.begin(String(IP) + "/tasks/last_update");
        int code = http.GET();

        if (code == 200){
        String payload = http.getString();
        http.end();
        StaticJsonDocument<128> doc; 
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.printf("JSON parse failed!: %s\n", error);
        }
        last_update = doc["unix_last_update"];
        }
        else http.end();

        showIcon = false;
    }
    catch (...) {
        return;
    }
}

bool get_task_by_id(StaticJsonDocument<1024> &task, const char* id){
    showIcon = true;
    try{
        HTTPClient http;
        http.begin(String(IP) + "/tasks/" + String(id));
        int code = http.GET();
        if (code == 200){
            String payload = http.getString();
            http.end();
            DeserializationError error = deserializeJson(task, payload);
            if (error) {
                Serial.printf("JSON parse failed!: %s\n", error);
                return false;
            }
            showIcon = false;
            return true;
        }
        else http.end();

        return false;
    }
    catch (...){
        return false;
    }
}

bool remove_task_id(const char* id){
    showIcon = true;
    try{
        HTTPClient http;
        http.begin(String(IP) + "/tasks/" + String(id));
        int code = http.sendRequest("DELETE");
        if (code == 204){
            http.end();
            showIcon = false;
            return true;
        }
        else http.end();
        
        return false;
    }
    catch(...){
        return false;
    }
}