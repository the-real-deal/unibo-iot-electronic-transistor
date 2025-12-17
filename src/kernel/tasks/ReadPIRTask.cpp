#include "ReadPIRTask.hpp"

ReadPIRTask::~ReadPIRTask()
{
}

void ReadPIRTask::init()
{
    Task::init();
}

void ReadPIRTask::tick()
{
    pir.calibrate();
    
    while(!pir.isDetected()){
        pir.sync();
    }
    setCompleted();

}

