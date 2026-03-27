#include "Arduino.h"
#include "Scheduler_Impl.hpp"
#include "Logger.h"

Scheduler_Impl::Scheduler_Impl(long period) : period(period)
{
    queue = LinkedList<Task *>();
    tasksToRemove = LinkedList<int>();
}

Scheduler_Impl::~Scheduler_Impl()
{
    queue.clear();
    tasksToRemove.clear();

    // delete queue;
    // delete tasksToRemove;
}

void Scheduler_Impl::addTask(Task *t)
{
    Logger.log(String(t->getId()));
    queue.add(t);
}

void Scheduler_Impl::executeTask()
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
                    currentTask->execute();
                }
            }
            else
            {
                currentTask->execute();
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

#define DEBUG
#ifdef DEBUG
    Logger.log("Total tasks in queue: " + String(queue.size()));
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
    while (tasksToRemove.size() > 0)
    {
        int idToRemove = tasksToRemove.pop();
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