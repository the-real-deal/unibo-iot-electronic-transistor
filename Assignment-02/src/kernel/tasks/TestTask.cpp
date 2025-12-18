#include "..\Task.hpp"
#include "..\Scheduler.hpp"
#include "LCDPrintTask.cpp"
#include "LedBlinkTask.cpp"
#include "ReadPIRTask.cpp"
#include "ReadSonarTask.cpp"
#include "SweepingBWDTask.cpp"
#include "SweepingFWDTask.cpp"

class TestTask : public Task
{
private:
    Scheduler *scheduler;
    /* data */
public:
    TestTask(Scheduler *scheduler);
    ~TestTask();

    void excecute() override;
    void cleanup() override;
};

TestTask::TestTask(Scheduler *scheduler_) : scheduler(scheduler_) {}

TestTask::~TestTask()
{
}

void TestTask::excecute()
{
}

void TestTask::cleanup()
{
}
