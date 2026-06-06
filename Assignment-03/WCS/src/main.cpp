#include <Arduino.h>
#include "model/HWPlatform.hpp"
#include "utils/MsgService.hpp"

HWPlatform hwPlatform;

void setup()
{
    MsgService.init();
    delay(2000);
    hwPlatform.init();
}

void loop()
{
    // Read inputs (btn potentiometer and serial message) and add events (btn pressed, pot moved, msg Recv)
    // context.Handle events
}
