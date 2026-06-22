#include "taskApp.h"

#include "lightSensor.h"
#include "pins.h"
#include "button.h"
#include "config.h"
#include "encoder.h"
#include "screen.h"
#include "initHandler.h"

LightSensor lightSensor;
Button button{Pins::BTN, Config::DEBOUNCE_MS, Config::HOLD_MS};
Button encoderButton{Pins::ENC_SW, Config::DEBOUNCE_MS, Config::HOLD_MS};
Encoder encoder{Pins::ENC_DT, Pins::ENC_CLK};
Screen screen{Pins::TFT_CS, Pins::TFT_RST, Pins::TFT_DC, Pins::TFT_SDI, Pins::TFT_SCK, Pins::TFT_LED};

InitHandler initHandler(screen);

void TaskApp::begin(){
    initHandler.handle(screen.begin());
    delay(100);

    auto lightSensorResult = lightSensor.begin();
    initHandler.handle(lightSensorResult);

    initHandler.handle(button.begin());
    initHandler.handle(encoderButton.begin());

    initHandler.handle(encoder.begin());

    screen.setTextSize(Config::TEXT_SIZE);
    screen.clear();
    delay(100);
}

void TaskApp::update(){
}