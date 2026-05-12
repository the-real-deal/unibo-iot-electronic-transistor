#include "Context.hpp"
#include "model/messageManager/Logger.h"

Context::Context() : hangarState(nullptr), securityState(nullptr), scheduler(nullptr), holder(nullptr) {}

Context::~Context()
{
    delete hangarState;
    delete securityState;
}

void Context::init(Scheduler *sched, InputHolder *hold)
{
    this->scheduler = sched;
    this->holder = hold;
}

void Context::setHangarState(HangarState *state)
{
    if (this->hangarState != nullptr)
    {
        delete this->hangarState;
    }
    this->hangarState = state;
    this->hangarState->setContext(this);
    this->hangarState->initializeTasks();
}

void Context::setSecurityState(SecurityState *state)
{
    if (this->securityState != nullptr)
    {
        delete this->securityState;
    }
    this->securityState = state;
    this->securityState->setContext(this);
    this->securityState->initializeTasks();
}

void Context::checkUpdate(ContextType destinationCtx)
{
    if (destinationCtx == ContextType::SECURITY)
        this->securityState->checkUpdate();
    else
        this->hangarState->checkUpdate();
}

void Context::handleDRURequest()
{
    if (this->securityState->canReceiveMsg())
    {
        this->hangarState->checkUpdate();
    }
}

void Context::addTaskToScheduler(Task *task, int period)
{
    if (period > 0)
    {
        task->init(period);
    }
    else
    {
        task->init();
    }
    this->scheduler->addTask(task);
}

void Context::removeTaskFromScheduler(int id)
{
    this->scheduler->removeTask(id);
}