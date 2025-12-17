#include "ReadSonarTask.hpp"

ReadSonarTask::~ReadSonarTask()
{
}

void ReadSonarTask::init()
{
    Task::init();
}

void ReadSonarTask::tick()
{
    
    sonar.setTemperature(temperature);
    sonar.getDistance();
    setCompleted();
}
