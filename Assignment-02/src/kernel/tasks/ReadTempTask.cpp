#include "ReadTempTask.hpp"

ReadTempTask::~ReadTempTask()
{
}

void ReadTempTask::cleanup()
{
}

void ReadTempTask::excecute()
{
    tempSensor->getTemperature();
    // setCompleted();
}
