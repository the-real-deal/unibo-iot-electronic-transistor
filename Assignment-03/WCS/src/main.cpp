#include <Arduino.h>
#include "model/HWPlatform.hpp"
#include "utils/MsgService.hpp"
#include "events/EventManager.hpp"
#include "model/Context.hpp"
#include "model/states/AutomaticState.hpp"
#include "utils/debug.hpp"

HWPlatform *hwPlatform;
Context *context;
EventManager *eventManager;

void setup()
{
    MsgService.init();
    delay(2000);

    hwPlatform = new HWPlatform();
    eventManager = new EventManager();
    context = new Context();

    hwPlatform->init();
    eventManager->setHwPlatform(hwPlatform);
    context->setHwPlatform(hwPlatform);
    eventManager->setListener(context);
    context->setCurrentState(new AutomaticState(StateEnum::AUTOMATIC));
}

void loop()
{
    long currentTime = millis();
    eventManager->checkEvents();
    eventManager->notify();
    long elapsedTime = millis() - currentTime;
    if (elapsedTime < PERIOD)
    {
        delay(PERIOD - elapsedTime);
    }
}
