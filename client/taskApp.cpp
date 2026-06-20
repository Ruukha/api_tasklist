#include "taskApp.h"

#include "lightSensor.h"
#include "pins.h"
#include "button.h"
#include "config.h"

LightSensor lightSensor;
Button button{BTN, DEBOUNCE_MS, HOLD_MS};
Button encoderButton{ENC_SW, DEBOUNCE_MS, HOLD_MS};

void TaskApp::begin(){
    Serial.begin(115200);
    
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(100000);

    lightSensor.begin();

    button.begin();
    encoderButton.begin();
}

void TaskApp::update(){
    
}