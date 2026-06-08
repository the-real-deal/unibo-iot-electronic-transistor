#include "events/EventManager.hpp"
#include "EventManager.hpp"
#include "utils/MsgService.hpp"

#include "configs.h"

EventManager::EventManager() : listener(nullptr), hwPlatform(nullptr) {}

void EventManager::setListener(EventListener *context)
{
    if (this->listener == nullptr)
    {
        this->listener = context;
    }
}

void EventManager::setHwPlatform(HWPlatform *HWPlatform)
{
    if (this->hwPlatform == nullptr)
    {
        this->hwPlatform = hwPlatform;
    }
}

void EventManager::subscribe(Event event)
{
    if (isSubscribed(event) < 0)
    {
        this->subscribedEvents.add(event);
    }
}

void EventManager::unsubscribeAll()
{
    this->subscribedEvents.clear();
}

void EventManager::notify()
{
    int size = events.size();
    while (events.size() > 0)
    {
        Event e = events.shift();
        if (isSubscribed(e))
            this->listener->update(e);
    }
}

void EventManager::checkEvents()
{
    int raw = hwPlatform->getPotentiometer()->getValue();
    bool isPressed = hwPlatform->getButton()->isPressed();

    /**
     * Check potentiometer
     * -----------------------
     */
    int value = map(raw, 0, 1023, 0, 100);
    if (abs(value - lastPotValue) > 2)
    {
        lastPotValue = value;
        lastChangeTime = millis();
        potEventPending = true;
    }
    if (potEventPending && (millis() - lastChangeTime >= POT_DEBOUNCE_TIME))
    {
        potEventPending = false;
        // stableValue = lastValue;
        // fire event(last value);
    }
    /**
     * -----------------------
     * Check button
     * -----------------------
     */
    if (isPressed && !lastBtnValue)
    {
        this->events.add(Event::BUTTON_EVENT);
    }
    lastBtnValue = isPressed;

    /**
     * Check messages
     */
    if (MsgService.isMsgAvailable())
    {
        this->events.add(Event::MESSAGE_EVENT);
    }
}

int EventManager::isSubscribed(Event event)
{
    for (int i = 0; i < this->subscribedEvents.size(); i++)
    {
        if (this->subscribedEvents.get(i) == event)
        {
            return i;
        }
    }
    return -1;
}
