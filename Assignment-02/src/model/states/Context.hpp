#pragma once
#include "HangarState.hpp"
#include "SecurityState.hpp"

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

    void changeState();
};