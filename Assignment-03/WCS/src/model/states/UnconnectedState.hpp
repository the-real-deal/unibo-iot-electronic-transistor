#pragma once
#include "model/states/State.hpp"

class UnconnectedState : public State
{
public:
    UnconnectedState(StateEnum state) : State(state) {}
    void manageEvents() override;
};