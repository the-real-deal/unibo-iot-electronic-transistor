#include <Arduino.h>
#include "config.h"
#include "kernel/MsgService.h"
#include "kernel/Scheduler_Impl.hpp"
#include "model/HWPlatform.hpp"
#include "kernel/tasks/LedBlinkTask.cpp"

Scheduler *scheduler;
HWPlatform *hwPlatform;

void setup()
{
  scheduler = new Scheduler_Impl(SCHEDULER_PERIOD_MS);
  /*
    Add Tasks to the scheduler here
  */

  // Task *test = new TestTask(scheduler);
  // test->init(3000);

  // Task *tmpTask = new LedBlinkTask(new Led(3));
  // tmpTask->init(500);
  // scheduler->addTask(tmpTask);
}

void loop()
{
  scheduler->excecuteTask();
}
