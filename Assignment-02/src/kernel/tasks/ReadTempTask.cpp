#include "ReadTempTask.hpp"

ReadTempTask::~ReadTempTask()
{
}

void ReadTempTask::cleanup()
{
}

void ReadTempTask::execute()
{
    tempSensor->getTemperature();
    // setCompleted();
}
