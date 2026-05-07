#include "Context.hpp"

Context::Context(Scheduler *sched, InputHolder *holder) : hangarState(nullptr), securityState(nullptr), scheduler(sched), holder(holder) {}

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

// String Context::getStateInfo()
// {
//     String sec = this->securityState->getStateInfo();
//     return sec.length() > 0 ? sec : this->hangarState->getStateInfo();
// }

void Context::handleDRURequest()
{
    if (this->securityState->canReceiveMsg())
    {
        this->hangarState->checkUpdate();
    }
}

void Context::addTaskToScheduler(Task *task, int period)
{
    this->scheduler->addTask(task);
    if (period > 0)
    {
        task->init(period);
    }
    else
    {
        task->init();
    }
}

void Context::removeTaskFromScheduler(int id)
{
    this->scheduler->removeTask(id);
}