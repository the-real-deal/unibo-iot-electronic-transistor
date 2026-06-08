#include <Arduino.h>
#include "model/HWPlatform.hpp"
#include "utils/MsgService.hpp"
#include "events/EventManager.hpp"
#include "model/Context.hpp"

HWPlatform hwPlatform;
Context context;
EventManager eventManager;

void setup()
{
    MsgService.init();
    delay(2000);
    hwPlatform.init();
    eventManager.setHwPlatform(&hwPlatform);
    eventManager.setListener(&context);
}

void loop()
{
    eventManager.checkEvents();
    eventManager.notify();
}
