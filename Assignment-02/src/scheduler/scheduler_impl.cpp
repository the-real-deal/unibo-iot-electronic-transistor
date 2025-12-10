#include "scheduler_impl.hpp"

Scheduler_Impl::Scheduler_Impl() {}

Scheduler_Impl::~Scheduler_Impl()
{
    queue.clear();
}

bool Scheduler_Impl::addTask(Task t)
{
    queue.add(t);
    return false;
}

bool Scheduler_Impl::removeTask(int id)
{
    return false;
}

void Scheduler_Impl::excecuteTask()
{
}

void Scheduler_Impl::clearQueue()
{
}
