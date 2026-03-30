#include "Context.hpp"

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

void Context::checkUpdate(String sender)
{
    if (sender == "SEC")
        this->securityState->checkUpdate();
    else
        this->hangarState->checkUpdate();
}

String Context::getStateInfo()
{
    String sec = this->securityState->getStateInfo();
    return sec.length() > 0 ? sec : this->hangarState->getStateInfo();
}

void Context::handleDRURequest(String msg)
{
    if (this->securityState->canReceiveMsg())
    {
        this->hangarState->handleRequest(msg);
    }
}

void Context::addTaskToScheduler(Task *task)
{
    this->scheduler->addTask(task);
}