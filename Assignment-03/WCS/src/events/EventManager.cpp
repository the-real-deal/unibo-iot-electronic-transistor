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

void EventManager::setHwPlatform(HWPlatform *_HWPlatform)
{
    if (this->hwPlatform == nullptr)
    {
        this->hwPlatform = _HWPlatform;
    }
}

void EventManager::subscribe(Event event)
{
    if (subscribedEventIndex(event) < 0)
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
    while (events.size() > 0)
    {
        Event e = events.shift();
        if (subscribedEventIndex(e) >= 0)
        {
            this->listener->update(e);
        }
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
    int value = raw;
    if (abs(value - lastPotValue) > POT_DEBOUNCE_VALUE)
    {
        lastPotValue = value;
        lastChangeTime = millis();
        potEventPending = true;
    }

    if (potEventPending && (millis() - lastChangeTime >= POT_DEBOUNCE_TIME))
    {
        potEventPending = false;
        this->events.add(Event::POTENTIOMETER_EVENT);
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

int EventManager::subscribedEventIndex(Event event)
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
