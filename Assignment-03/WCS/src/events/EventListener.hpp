/**
 * Part of the observer pattern
 */
#pragma once
#include "events/Event.hpp"

/**
 * Interface used to make any class an event listener
 */
class EventListener
{
public:
    /**
     * Method called when an event is fired
     * @param event The event fired
     */
    virtual void update(Event event) = 0;
};