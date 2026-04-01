#pragma once

#include "../Task.hpp"
#include "../../devices/Pir.h"
#include "../../model/states/Context.hpp"
#include "../../model/InputHolder.hpp"

class ReadPIRTask : public Task
{

private:
    Pir *pir;
    Context *context;
    InputHolder *holder;
    ContextType ctxToNotify;
    
public:

    /**
     * @param pir The sensor
     * @param ctx The context of the application, containing the current states
     * @param holder The class maintaining the current values of all the sensor
     * @param notifyHangar True if the sensor, after the read, has to notify either the hangar or the security context
     */
    ReadPIRTask(Pir *pir, Context *ctx, InputHolder *holder, ContextType destCtx);
    virtual ~ReadPIRTask() = default;

    void execute() override;
    void cleanup() override;
};