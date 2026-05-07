#include <Arduino.h>
#include "config.h"
#include "model/messageManager/MsgService.h"
#include "kernel/Scheduler_Impl.hpp"
#include "model/HWPlatform.hpp"
#include "model/messageManager/Logger.h"
// #include "kernel/tasks/LCDPrintTask.hpp"
#include "kernel/tasks/LedBlinkTask.hpp"
// #include "kernel/tasks/ReadPIRTask.hpp"
// #include "kernel/tasks/ReadDistanceTask.hpp"

/**
 * FSM diagram
 * https://lucid.app/lucidchart/c60760fd-f278-41b0-a28d-a48a83edcd56/edit?invitationId=inv_fc43df35-97c2-42f9-a25e-338626ab2d3e&page=0_0#
 */

Scheduler_Impl scheduler(SCHEDULER_PERIOD_MS);
HWPlatform hwPlatform;

void setup()
{
  MsgService.init();

  hwPlatform.setup();

  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  Serial.println("Begin");
  Serial.flush();

  hwPlatform.getLed2()->switchOn();

  Task *lb2 = new LedBlinkTask(hwPlatform.getLed2());
  Task *lb3 = new LedBlinkTask(hwPlatform.getLed3());

  lb2->init(500);
  lb3->init(500);

  scheduler.addTask(lb2);
  scheduler.addTask(lb3);
}

void loop()
{
  scheduler.executeTask();
}
