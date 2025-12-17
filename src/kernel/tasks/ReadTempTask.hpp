#pragma once
#include "../task.hpp"
#include "../../devices/TempSensorImpl.hpp"


class ReadTempTask : public Task {

    private:
    TempSensorDHT11 tempSensor;
    

    public:
    ReadTempTask(TempSensorDHT11 tempSensor) : tempSensor(tempSensor) {};
    ~ReadTempTask();
    
    virtual void init() = 0;
    virtual void tick() = 0;
};