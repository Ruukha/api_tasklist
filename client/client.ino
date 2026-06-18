#include "lightSensor.h"
#include "pins.h"

void setup(){
    Serial.begin(115200);
    
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(100000);

    // light sensor init
    LightSensor lightSensor;
    lightSensor.begin();
}

void loop(){
    
}