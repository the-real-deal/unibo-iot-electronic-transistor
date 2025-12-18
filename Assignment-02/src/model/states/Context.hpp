#pragma once
#include "../../kernel/Task.hpp"
#include "../../kernel/Scheduler.hpp"
#include "../HWPlatform.hpp"
#include <Arduino.h>

/* State Classes Definition */
class HangarState;
class SecurityState;
enum HangarSubState
{
    CHECKING,
    OPENING,
    DETECTING,
    CLOSING
};
/* ------------------------ */

class Context
{
private:
    HangarState *hangarState;
    SecurityState *securityState;
    Scheduler *scheduler;

public:
    Context(Scheduler *sched) : hangarState(nullptr), securityState(nullptr), scheduler(sched) {};
    ~Context();

    /*
     * Setters for the hangar state, method called by the states themselves
     */
    void setHangarState(HangarState *state);
    /*
     * Setters for the security state, method called by the states themselves
     */
    void setSecurityState(SecurityState *state);

    /*
     * Method to change state, called by external events (ex. tasks)
     */
    void changeState(String sender);

    /*
     * Method to get current state info (used to print on the LCD)
     */
    String getStateInfo();

    /*
     * Method to handle incoming DRU requests
     */
    void handleDRURequest(String msg);

    /*
     * Method to add tasks to the scheduler
     */
    void addTaskToScheduler(Task *task);
};

/* State Class Definition */
class HangarState
{
private:
protected:
    Context *context;
    int *taskAdded;

public:
    HangarState();
    virtual ~HangarState()
    {
        delete taskAdded;
    }

    void setContext(Context *ctx)
    {
        this->context = ctx;
    }

    /*
     * Adds all the necessary tasks for the state
     */
    virtual void initializeTasks(HWPlatform *platform);

    /*
     * Gets all the data to send to the DRU
     */
    virtual String sendDRUData();

    /*
     * Gets information about the current state (used for LCD display)
     */
    virtual String getStateInfo();

    /*
     * Method to change state, called by external events (ex. tasks)
     */
    virtual void changeState();

    /*
     * Method to handle incoming DRU requests
     */
    virtual void handleRequest(String msg);
};

class SecurityState
{
private:
protected:
    Context *context;

public:
    SecurityState(/* args */);
    virtual ~SecurityState();

    void setContext(Context *ctx)
    {
        this->context = ctx;
    }

    /*
     * Adds all the necessary tasks for the state
     */
    virtual void initializeTasks(HWPlatform *platform);

    /*
     * Method to check if the current state can receive messages
     */
    virtual bool canReceiveMsg();

    /*
     * Gets all the data to send to the DRU
     */
    virtual String sendDRUData();

    /*
     * Gets information about the current state (used for LCD display)
     */
    virtual String getStateInfo();

    /*
     * Method to change state, called by external events (ex. tasks)
     */
    virtual void changeState();
};
