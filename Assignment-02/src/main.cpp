#include <Arduino.h>
#include "config.h"
#include "kernel/MsgService.h"
#include "kernel/Scheduler_Impl.hpp"
#include "model/HWPlatform.hpp"
#include "kernel/Logger.h"
// #include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/LedBlinkTask.hpp"
// #include "kernel/tasks/ReadPIRTask.hpp"
// #include "kernel/tasks/ReadDistanceTask.hpp"

/**
 * FSM diagram
 * https://lucid.app/lucidchart/c60760fd-f278-41b0-a28d-a48a83edcd56/edit?invitationId=inv_fc43df35-97c2-42f9-a25e-338626ab2d3e&page=0_0#
*/

Scheduler *scheduler;
HWPlatform *hwPlatform;

void setup()
{
  delay(1000);
  MsgService.init();

  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);

  scheduler = new Scheduler_Impl(SCHEDULER_PERIOD_MS);

  Led *l2 = new Led(LED2);
  l2->switchOn();

  Led *l3 = new Led(LED3);
  Task *lbt2 = new LedBlinkTask(l3);
  lbt2->init(500);
  Task *ledBlinkTask = new LedBlinkTask(l2);
  scheduler->addTask(ledBlinkTask);
  ledBlinkTask->init(500);
  scheduler->addTask(lbt2);
  /*
    Add Tasks to the scheduler here
  */
}

void loop()
{
  scheduler->executeTask();
}
