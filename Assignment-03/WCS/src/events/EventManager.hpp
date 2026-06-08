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
#include "model/HWPlatform.hpp"
#include <LinkedList.h>

class EventManager
{
public:
    EventManager();
    ~EventManager() = default;

    /**
     * Sets the listener
     */
    void setListener(EventListener *context);

    /**
     * Sets the hardware devices
     */
    void setHwPlatform(HWPlatform *HWPlatform);

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
    void notify();

    /**
     * Listens to the events
     */
    void checkEvents();

private:
    /**
     * Checks if the listener is subscribed to the given event
     * @returns the index of the event in the list, -1 if the listener is not subscribed
     */
    int subscribedEventIndex(Event event);

    EventListener *listener;
    HWPlatform *hwPlatform;

    bool lastBtnValue = false;
    bool btnEventPending = false;
    int lastPotValue = -1;
    unsigned long lastChangeTime = 0;
    bool potEventPending = false;

    LinkedList<Event> subscribedEvents;
    LinkedList<Event> events;
};

extern EventManager *eventManager;