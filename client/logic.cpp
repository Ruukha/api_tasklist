#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "logic.h"
#include "screen.h"
#include "config.h"

void update(Adafruit_ILI9341 &tft){
  tft.setCursor(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  HTTPClient http;
  http.begin(String(IP) + "/tasks");
  int code = http.GET();
  Serial.printf("HTTP status code: %d\n", code);
  if (code == 200){
    String payload = http.getString();
    http.end();
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
  else http.end();

  last_cached_update = last_update;
}

void get_last_update(){
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
}
