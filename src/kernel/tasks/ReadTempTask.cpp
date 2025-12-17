#include "ReadTempTask.hpp"

ReadTempTask::~ReadTempTask()
{
}

void ReadTempTask::init()
{
    Task::init();
}

void ReadTempTask::tick()
{
    tempSensor.getTemperature();
    setCompleted();
}
