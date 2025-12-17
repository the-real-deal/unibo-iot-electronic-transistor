#pragma once

#include "../task.hpp"
#include "../../devices/sonar.h"

class ReadSonarTask : public Task
{

private:
    Sonar *sonar;
    float temperature;

public:
    ReadSonarTask(Sonar *sonar, float temperature) : sonar(sonar), temperature(temperature)
    {
        sonar->setTemperature(temperature);
    };
    ~ReadSonarTask();

    void excecute() override;
    void cleanup() override;
};