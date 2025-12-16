#include "Arduino.h"
#include "scheduler_impl.hpp"

Scheduler_Impl::~Scheduler_Impl()
{
    queue.clear();
}

void Scheduler_Impl::addTask(Task *t)
{
    queue.add(t);
}

void Scheduler_Impl::excecuteTask()
{
    long currentTime = millis();
    for (int i = 0; i < queue.size(); i++)
    {
        Task *currentTask = queue.get(i);
        if (currentTask->isActive())
        {
            if (currentTask->isPeriodic())
            {
                if (currentTask->updateAndCheckTime(period))
                {
                    currentTask->excecute();
                }
            }
            else
            {
                currentTask->excecute();
            }
            if (currentTask->isCompleted())
            {
                queue.remove(i);
                i--; // Adjust index after removal
            }
        }
    }

    long elapsedTime = millis() - currentTime;
    if (elapsedTime < period)
    {
        delay(period - elapsedTime);
    }

#ifdef DEBUG
    Logger.log("------ Scheduler Information ------");
    Logger.log("Total tasks in queue: " + String(queue.size()));
    Logger.log("Period length: " + String(period));
    Logger.log("Elapsed time: " + String(elapsedTime));
    Logger.log("-----------------------------------");
#endif
}

void Scheduler_Impl::clearQueue()
{
    queue.clear();
}

void Scheduler_Impl::removeTask(int id)
{
    for (int i = 0; i < queue.size(); i++)
    {
        if (queue.get(i)->getId() == id)
        {
            queue.remove(i);
            break;
        }
    }
}