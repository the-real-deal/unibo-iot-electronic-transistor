#pragma once

class InputHolder
{
private:
    float temperature;
    long distance;
    bool motionDetected;

public:
    InputHolder();
    ~InputHolder();

    void setTemperature(float temp);
    void setDistance(long dist);
    void setMotionDetected(bool detected);

    float getTemperature();
    long getDistance();
    bool isMotionDetected();
};
