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
    int size = queue.size();
    for (int i = 0; i < size; i++)
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
                removeTask(currentTask->getId());
            }
        }
    }

    removeTaskFromQueue();

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
    tasksToRemove.add(id);
}

void Scheduler_Impl::removeTaskFromQueue()
{
    for (int i = 0; i < tasksToRemove.size(); i++)
    {
        int idToRemove = tasksToRemove.get(i);
        for (int j = 0; j < queue.size(); j++)
        {
            if (queue.get(j)->getId() == idToRemove)
            {
                queue.remove(j);
                break;
            }
        }
    }
}