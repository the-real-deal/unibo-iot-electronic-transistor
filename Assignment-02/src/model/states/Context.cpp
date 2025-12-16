#include "Context.hpp"

Context::Context() : securityState(nullptr), hangarState(nullptr)
{
}

Context::~Context()
{
    delete hangarState;
    delete securityState;
}

void Context::setHangarState(HangarState *state)
{
    if (this->hangarState != nullptr)
    {
        delete this->hangarState;
    }
    this->hangarState = state;
    this->hangarState->setContext(this);
}

void Context::setSecurityState(SecurityState *state)
{
    if (this->securityState != nullptr)
    {
        delete this->securityState;
    }
    this->securityState = state;
    this->securityState->setContext(this);
}

void Context::changeState(String sender)
{
    if (sender == "SEC")
        this->securityState->changeState();
    else
        this->hangarState->changeState();
}

String Context::getStateInfo()
{
    String sec = this->securityState->getStateInfo();
    return sec.length() > 0 ? sec : this->hangarState->getStateInfo();
}