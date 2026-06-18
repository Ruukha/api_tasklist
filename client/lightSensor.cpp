#include <BH1750_WE.h>
#include <Wire.h>

#include "lightSensor.h"

constexpr uint8_t BH1750_ADDR = 0x23;

LightSensor::LightSensor()
    : sensor(BH1750_ADDR)
{}

bool LightSensor::begin(){
    bool success = sensor.init();

    Serial.print("Light sensor init: ");
    Serial.println(success ? "OK" : "ERROR");

    return success;
}

float LightSensor::read(){
    return sensor.getLux();
}