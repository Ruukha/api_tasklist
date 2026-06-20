#include <Wire.h>

#include "taskApp.h"
#include "pins.h"

TaskApp app;

void setup(){
    Serial.begin(115200);
    
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(100000);
    app.begin();
}

void loop(){
    app.update();
}