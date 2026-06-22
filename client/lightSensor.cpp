#include <BH1750_WE.h>
#include <Wire.h>

#include "lightSensor.h"

constexpr uint8_t BH1750_ADDR = 0x23;

LightSensor::LightSensor()
    : sensor(BH1750_ADDR)
{}

InitResult LightSensor::begin(){
    if (sensor.init()){
        return {InitStatus::OK, "Light sensor"};
    }
    return {InitStatus::Warning, "Light sensor", "Not detected"};
}

float LightSensor::read(){
    return sensor.getLux();
}