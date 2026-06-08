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
    // Read inputs (btn potentiometer and serial message) and add events (btn pressed, pot moved, msg Recv)
    // context.Handle events
}
