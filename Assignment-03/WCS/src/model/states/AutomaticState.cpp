#include "model/states/AutomaticState.hpp"
#include "events/EventManager.hpp"

void AutomaticState::manageEvents()
{
    eventManager.unsubscribeAll();
    eventManager.subscribe(Event::BUTTON_EVENT);
    eventManager.subscribe(Event::MESSAGE_EVENT);
}