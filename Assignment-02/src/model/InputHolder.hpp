#pragma once

class InputHolder
{
private:
    float temperature;
    float distance;
    bool motionDetected;

public:
    InputHolder();
    ~InputHolder();

    void setTemperature(float temp);
    void setDistance(float dist);
    void setMotionDetected(bool detected);

    float getTemperature();
    float getDistance();
    bool isMotionDetected();
};
