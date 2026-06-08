#pragma once
#include "model/states/State.hpp"

class ManualState : public State
{
public:
    ManualState(StateEnum state) : State(state) {}
    void manageEvents() override;
};
