#include "model/states/UnconnectedState.hpp"
#include "events/EventManager.hpp"

void UnconnectedState::manageEvents()
{
    eventManager.unsubscribeAll();
    eventManager.subscribe(Event::MESSAGE_EVENT);
}