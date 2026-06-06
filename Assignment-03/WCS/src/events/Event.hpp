#pragma once

enum EventType
{
    BUTTON_EVENT,
    POTENTIOMETER_EVENT,
    MESSAGE_EVENT
};

class Event
{
public:
    Event(EventType event);
    virtual ~Event() = default;

    EventType getEventType()
    {
        return this->type;
    }

private:
    EventType type;
};