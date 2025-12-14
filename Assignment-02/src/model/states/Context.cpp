#include "Context.hpp"

Context::Context() : securityState(nullptr), hangarState(nullptr)
{
    // this->hangarState = /* new idle */;
    // this->securityState = /* new normal */;
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
