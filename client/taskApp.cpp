#include "taskApp.h"

#include "lightSensor.h"
#include "pins.h"
#include "button.h"
#include "config.h"

LightSensor lightSensor;
Button button{Pins::BTN, Config::DEBOUNCE_MS, Config::HOLD_MS};
Button encoderButton{Pins::ENC_SW, Config::DEBOUNCE_MS, Config::HOLD_MS};

void TaskApp::begin(){
    lightSensor.begin();

    button.begin();
    encoderButton.begin();
}

void TaskApp::update(){
    
}