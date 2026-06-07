/**
 * Part of the observer pattern (Subject)
 * Observer pattern concepts taken from:
 * Title: Design Patterns: Elements of Reusable Object-Oriented Software
 * Author: Gang of Four
 * Pages: 293-304
 * Simplified version, because there is only one listener
 */
#pragma once

#include "events/EventListener.hpp"
#include "events/Event.hpp"
#include <LinkedList.h>

class EventManager
{
public:
    ~EventManager() = default;

    /**
     * Sets the listener
     */
    void setListener(EventListener *context);

    /**
     * Subscribes the listener to an event
     */
    void subscribe(Event event);

    /**
     * Unsubscribes the listener to all events
     */
    void unsubscribeAll();

    /**
     * Notifies the listener to the subscribed event
     */
    void notify(Event event);

private:
    EventManager() : listener(nullptr) {};

    /**
     * Checks if the listener is subscribed to the given event
     * @returns the index of the event in the list, -1 if the listener is not subscribed
     */
    int isSubscribed(Event event);

    EventListener *listener;
    LinkedList<Event> subscribedEvents;
};

extern EventManager eventManager;