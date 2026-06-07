#include "events/EventManager.hpp"
#include "EventManager.hpp"

void EventManager::setListener(EventListener *context)
{
    if (this->listener == nullptr)
    {
        this->listener = context;
    }
}

void EventManager::subscribe(Event event)
{
    if (isSubscribed(event) < 0)
    {
        this->subscribedEvents.add(event);
    }
}

void EventManager::unsubscribe(Event event)
{
    int index = isSubscribed(event);
    if (index >= 0)
    {
        this->subscribedEvents.remove(index);
    }
}

void EventManager::notify(Event event)
{
    if (isSubscribed(event) >= 0)
    {
        this->listener->update(event);
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
