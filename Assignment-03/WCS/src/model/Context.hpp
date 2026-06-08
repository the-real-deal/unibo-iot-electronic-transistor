#pragma once
#include "model/states/State.hpp"
#include "events/Event.hpp"
#include "events/EventListener.hpp"
#include "model/HWPlatform.hpp"

class Context : public EventListener
{
public:
    Context();
    ~Context();

    /*
     * Changes the current state, method called by the states themselves
     */
    void setCurrentState(State *state);

    /**
     * Sets the hw platform class
     */
    void setHwPlatform(HWPlatform *plt);

    /**
     * Handles the given event
     * @param event the event to handle
     */
    void update(Event event) override;

private:
    State *currentState;
    HWPlatform *hwPlatform;
};
