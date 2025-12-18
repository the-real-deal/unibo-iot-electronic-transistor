#include "InputHolder.hpp"

InputHolder::InputHolder() : temperature(0.0), distance(0), motionDetected(false) {}
InputHolder::~InputHolder() {}

void InputHolder::setTemperature(float temp)
{
    this->temperature = temp;
}

void InputHolder::setDistance(long dist)
{
    this->distance = dist;
}

void InputHolder::setMotionDetected(bool detected)
{
    this->motionDetected = detected;
}

float InputHolder::getTemperature()
{
    return this->temperature;
}