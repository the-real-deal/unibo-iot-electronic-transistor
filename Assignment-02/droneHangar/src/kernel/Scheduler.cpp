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
    this->clearQueue();
    tasksToRemove.clear();
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
    for (int i = 0; i < queue.size(); i++)
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
    while (queue.size() > 0)
    {
        Task *toDelete = queue.shift();
        delete toDelete;
    }
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
                // [TODO] check if correct
                Task *toRemove = queue.remove(j);
                delete toRemove;
                break;
            }
        }
    }
}