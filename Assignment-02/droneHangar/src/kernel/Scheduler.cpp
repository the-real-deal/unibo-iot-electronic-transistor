#include "Arduino.h"
#include "model/messageManager/Logger.h"
#include "debug.hpp"
#include "Scheduler.hpp"
#include "model/Timer.hpp"

Scheduler::Scheduler(long period) : period(period), queue(), tasksToRemove(), builtIn(Led(LED_BUILTIN))
{
}

Scheduler::~Scheduler()
{
    queue.clear();
    tasksToRemove.clear();
    // delete queue;
    // delete tasksToRemove;
}

void Scheduler::addTask(Task *t)
{
    queue.add(t);
}

void Scheduler::executeTask()
{

    Serial.print(F("Free Memory: "));
    Serial.println(freeMemory());
    Serial.flush();
    long currentTime = millis();
    int size = queue.size();
    Serial.print(F("Queue Size: "));
    Serial.println(size);
    Serial.flush();
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
            // if (currentTask->isCompleted())
            // {
            //     removeTask(currentTask->getId());
            // }
        }
    }

    removeTaskFromQueue();

    if (builtIn.isOn())
        builtIn.switchOff();
    else
        builtIn.switchOn();

    long elapsedTime = millis() - currentTime;
    if (elapsedTime < period)
    {
        delay(period - elapsedTime);
    }
}

void Scheduler::clearQueue()
{
    queue.clear();
}

void Scheduler::removeTask(int id)
{
    tasksToRemove.add(id);
}

void Scheduler::removeTaskFromQueue()
{
    while (tasksToRemove.size() > 0)
    {
        int idToRemove = tasksToRemove.pop();
        for (int j = 0; j < queue.size(); j++)
        {
            Task *t = queue.get(j);
            if (t->getId() == idToRemove)
            {
                t->cleanup();
                queue.remove(j);
                break;
            }
        }
    }
}