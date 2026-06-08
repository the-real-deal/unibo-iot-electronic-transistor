#pragma once
#include "model/states/State.hpp"

class AutomaticState : public State
{
public:
    AutomaticState(StateEnum state) : State(state) {}
    ~AutomaticState() = default;

    void manageEvents() override;
};
