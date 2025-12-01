#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "logic.h"
#include "screen.h"
#include "config.h"

void update(Adafruit_ILI9341 tft){
  HTTPClient http;
  http.begin(IP + "/tasks");
  int code = http.GET();
  if (code == 200){
    String payload = http.getString();
    StaticJsonDocument<4096> doc; 
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        Serial.printf("JSON parse failed!: %s\n", error);
        return;
    }

    for (JsonPair kv : doc.as<JsonObject>()){
      String id = String(kv.key().c_str());
      String name = String(kv.value().as<const char*>());

      draw_task(id, name, tft);
    }
  }
  http.end();

  last_cached_update = time(nullptr);
}

void get_last_update(){
  HTTPClient http;
  http.begin(IP + "/tasks/last_update");
  int code = http.GET();
  if (code == 200){
    String payload = http.getString();
    StaticJsonDocument<128> doc; 
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        Serial.printf("JSON parse failed!: %s\n", error);
        return;
    }
    last_update = doc["updated_at"];
  }
  http.end();
}