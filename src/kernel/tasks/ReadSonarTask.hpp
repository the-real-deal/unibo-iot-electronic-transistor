#pragma once

#include "../task.hpp"
#include "../../devices/sonar.h"

class ReadSonarTask : public Task {

    private:
    Sonar sonar;
    float temperature;  

    public:
    ReadSonarTask(Sonar sonar, float temperature) : sonar(sonar), temperature(temperature){};
    ~ReadSonarTask();
    virtual void init() = 0;
    virtual void tick() = 0;
};