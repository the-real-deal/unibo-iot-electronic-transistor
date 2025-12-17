#pragma once
#include "../task.hpp"
#include "../../devices/TempSensor.h"

class ReadTempTask : public Task
{

private:
    TempSensor *tempSensor;

public:
    ReadTempTask(TempSensor *tempSensor) : tempSensor(tempSensor) {};
    ~ReadTempTask();

    void excecute() override;
    void cleanup() override;
};