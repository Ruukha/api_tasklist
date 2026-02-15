#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "logic.h"
#include "screen.h"
#include "config.h"

void update(Adafruit_ILI9341 &tft, StaticJsonDocument<4096> &tasks, int counter){
  if (!getPayload(tasks)){
    Serial.print("Payload not obtained\n");
    return;
  }

  scroll(tft, tasks, counter);
}

void scroll(Adafruit_ILI9341 &tft, StaticJsonDocument<4096> &tasks, int counter){
  StaticJsonDocument<2048> tasksToDraw;
  if (getSlice(tasks, tasksToDraw, counter, counter + tasks_cap)) draw_tasks(tft, tasksToDraw);
}

bool getSlice(StaticJsonDocument<4096> &doc, StaticJsonDocument<2048> &outDoc, int start, int end){
  outDoc.clear();

  Serial.printf("start: %i, end: %i\n", start, end);

  JsonObject inObj = doc.as<JsonObject>();
  JsonObject outObj = outDoc.to<JsonObject>();

  int idx = 0;
  int copied = 0;

  for (JsonPair kv : inObj) {
    if (idx >= start && idx < end) {
      outObj[kv.key().c_str()] = kv.value();
      copied++;
    }
    idx++;
    if (copied >= end) break;
  }

  return (copied > 0);
}

const char* getId(StaticJsonDocument<4096> &tasks, int counter){
  int idx = 0;
  for (JsonPair kv : tasks.as<JsonObject>()) {
    if (idx == counter) {
      return kv.key().c_str();
    }
    idx++;
  }
}