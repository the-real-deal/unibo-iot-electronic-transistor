#include "model/states/ManualState.hpp"
#include "events/EventManager.hpp"

void ManualState::manageEvents()
{
    eventManager.unsubscribeAll();
    eventManager.subscribe(Event::BUTTON_EVENT);
    eventManager.subscribe(Event::POTENTIOMETER_EVENT);
    eventManager.subscribe(Event::MESSAGE_EVENT);
}