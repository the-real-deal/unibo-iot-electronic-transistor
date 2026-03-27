#include "ReadTempTask.hpp"

ReadTempTask::ReadTempTask(TempSensor *tempSensor) : tempSensor(tempSensor) {}

void ReadTempTask::cleanup()
{
}

void ReadTempTask::execute()
{
    // tempSensor->getTemperature();
    // value holder.temperature = temperature;
}
