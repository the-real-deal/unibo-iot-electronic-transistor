#pragma once
#include "../Task.hpp"
#include "../../devices/TempSensor.h"

class ReadTempTask : public Task
{

private:
    TempSensor *tempSensor;

public:
    ReadTempTask(TempSensor *tempSensor);
    virtual ~ReadTempTask() = default;

    void execute() override;
    void cleanup() override;
};