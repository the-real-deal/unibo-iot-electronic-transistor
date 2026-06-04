#pragma once

#include <Arduino.h>

#define NO_OBJ_DETECTED -1

class Sonar
{

public:
    Sonar(int echoP, int trigP, long maxTime) : echoPin(echoP), trigPin(trigP), timeOut(maxTime)
    {
        temperature = 25; // default value
    }

    /**
     * Initializes the component, this must be called in the setup function
     */
    void init()
    {
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
    }

    /**
     * Method used to get the distance from the sonar
     * @return the distance in
     */
    float getDistance()
    {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(3);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(5);
        digitalWrite(trigPin, LOW);

        float tUS = pulseIn(echoPin, HIGH, timeOut);
        if (tUS == 0)
        {
            return NO_OBJ_DETECTED;
        }
        else
        {
            float t = tUS / 1000.0 / 1000.0 / 2 * getSoundSpeed();

            return t;
        }
    }

    void setTemperature(float temp)
    {
        temperature = temp;
    }

private:
    float getSoundSpeed()
    {
        return 331.5 + 0.6 * temperature;
    }

    float temperature;
    int echoPin, trigPin;
    long timeOut;
};
