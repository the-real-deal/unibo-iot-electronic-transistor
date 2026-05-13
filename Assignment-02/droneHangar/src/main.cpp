#include <Arduino.h>
#include "config.h"
#include "model/messageManager/MsgService.h"
#include "kernel/Scheduler.hpp"
#include "model/HWPlatform.hpp"
#include "model/messageManager/Logger.h"
// #include "debug.hpp"
#include "model/states/hangarStates/IdleState.hpp"
#include "model/states/securityStates/NormalState.hpp"
#include "model/states/hangarStates/OperativeState.hpp"

/**
 * FSM diagram
 * https://lucid.app/lucidchart/c60760fd-f278-41b0-a28d-a48a83edcd56/edit?invitationId=inv_fc43df35-97c2-42f9-a25e-338626ab2d3e&page=0_0#
 */
Scheduler scheduler(SCHEDULER_PERIOD_MS);
HWPlatform hwPlatform;
InputHolder holder;
Context ctx;

void setup()
{

  MsgService.init();

  hwPlatform.setup();

  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);

  ctx.init(&scheduler, &holder);

  ctx.setSecurityState(
      new NormalState(
          &hwPlatform,
          &holder));
  ctx.setHangarState(new IdleState(
      &hwPlatform,
      &holder));
}

void loop()
{
  scheduler.executeTask();
}
