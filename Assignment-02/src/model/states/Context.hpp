#pragma once
#include "HangarState.hpp"
#include "SecurityStates/SecurityState.hpp"
#include <Arduino.h>

class Context
{
private:
    HangarState *hangarState;
    SecurityState *securityState;

public:
    Context();
    ~Context();

    void setHangarState(HangarState *state);
    void setSecurityState(SecurityState *state);
    void changeState(String sender);

    String getStateInfo();
};