#include "Arduino.h"
#include "scheduler_impl.hpp"

Scheduler_Impl::Scheduler_Impl()
{
    this->index = 0;
}

Scheduler_Impl::~Scheduler_Impl()
{
    queue.clear();
}

void Scheduler_Impl::addTask(Task t)
{
    queue.add(t);
}

Task Scheduler_Impl::removeTask(int id)
{
    for (int i = 0; i < queue.size(); i++)
    {
        Task currentTask = queue.get(i);
        if (currentTask.getId() == id)
        {
            Task rm = queue.remove(i);
            return rm;
        }
    }
    return Task(0); // Return a default Task if not found
}

void Scheduler_Impl::excecuteTask()
{
    long currentTime = millis();
    if (queue.size() == 0)
        return;

    Task currentTask = queue.get(index);
    bool isFinished = currentTask.excecute();

    if (isFinished)
    {
        Task t = removeTask(currentTask.getId());
        delete &t;
    }
    else
    {
        index++;
    }

    if (index >= queue.size())
    {
        index = 0;
    }

    long elapsedTime = millis() - currentTime;
    if (elapsedTime < period)
    {
        delay(period - elapsedTime);
    }
}

void Scheduler_Impl::clearQueue()
{
    queue.clear();
    index = 0;
}
