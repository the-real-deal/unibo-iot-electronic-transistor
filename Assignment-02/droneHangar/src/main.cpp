#include <Arduino.h>
#include "config.h"
#include "model/messageManager/MsgService.h"
#include "kernel/Scheduler_Impl.hpp"
#include "model/HWPlatform.hpp"
#include "model/messageManager/Logger.h"

#include "kernel/tasks/LedBlinkTask.hpp"
// #include "kernel/tasks/ReadPIRTask.hpp"
#include "kernel/tasks/ReadDistanceTask.hpp"
// #include "kernel/tasks/ButtonTask.hpp"
// #include "kernel/tasks/ReadTempTask.hpp"
// #include "kernel/tasks/SweepingTask.hpp"
// #include "kernel/tasks/DRUReceiverTask.hpp"
#include "kernel/tasks/SendDistanceTask.hpp"

/**
 * FSM diagram
 * https://lucid.app/lucidchart/c60760fd-f278-41b0-a28d-a48a83edcd56/edit?invitationId=inv_fc43df35-97c2-42f9-a25e-338626ab2d3e&page=0_0#
 */

Scheduler_Impl scheduler(SCHEDULER_PERIOD_MS);
HWPlatform hwPlatform;
InputHolder holder;

void setup()
{
  MsgService.init();

  hwPlatform.setup();

  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);

  Task *t1 = new LedBlinkTask(hwPlatform.getLed2());
  Task *t2 = new LedBlinkTask(hwPlatform.getLed3());
  Task *t3 = new ReadDistanceTask(hwPlatform.getDistanceDetector(), nullptr, &holder, ContextType::HANGAR);
  Task *t4 = new SendDistanceTask(&holder);
  hwPlatform.getLed3()->switchOn();

  t1->init(500);
  t2->init(500);
  t3->init();
  t4->init(250);

  scheduler.addTask(t1);
  scheduler.addTask(t2);
  scheduler.addTask(t3);
  scheduler.addTask(t4);
}

void loop()
{
  scheduler.executeTask();
}
