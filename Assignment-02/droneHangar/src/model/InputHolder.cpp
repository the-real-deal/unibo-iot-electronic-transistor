#include "InputHolder.hpp"

InputHolder::InputHolder() : temperature(0.0), distance(0), motionDetected(false), message(""), pressed(false) {}
InputHolder::~InputHolder() {}

void InputHolder::setTemperature(float temp)
{
    this->temperature = temp;
}

void InputHolder::setDistance(float dist)
{
    this->distance = dist;
}

void InputHolder::setMotionDetected(bool detected)
{
    this->motionDetected = detected;
}

void InputHolder::setMessage(String msg)
{
    this->message = msg;
}

void InputHolder::setIsPressed(bool pressed)
{
    this->pressed = pressed;
}

float InputHolder::getTemperature()
{
    return this->temperature;
}

float InputHolder::getDistance()
{
    return this->distance;
}

bool InputHolder::isMotionDetected()
{
    return this->motionDetected;
}

String InputHolder::getMessage()
{
    return this->message;
}

bool InputHolder::isPressed()
{
    return this->pressed;
}