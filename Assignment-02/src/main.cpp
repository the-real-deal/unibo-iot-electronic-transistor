#include <Arduino.h>
#include "config.h"
#include "kernel/MsgService.h"
#include "kernel/Scheduler_Impl.hpp"

Scheduler_Impl scheduler;

void setup()
{
  scheduler = Scheduler_Impl(SCHEDULER_PERIOD_MS);
  /*
    Add Tasks to the scheduler here
  */
}

void loop()
{
  scheduler.excecuteTask();
}
