#pragma once
#include "HangarState.hpp"
#include "SecurityStates/SecurityState.hpp"
#include "../../kernel/Task.hpp"
#include "../../kernel/Scheduler.hpp"
#include <Arduino.h>

class Context
{
private:
    HangarState *hangarState;
    SecurityState *securityState;
    Scheduler *scheduler;

public:
    Context(Scheduler *sched) : scheduler(sched), securityState(nullptr), hangarState(nullptr) {};
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