#include "kernel/Task.hpp"
#include "model/InputHolder.hpp"

class SendDistanceTask : public Task
{
private:
    InputHolder *holder;

public:
    SendDistanceTask(InputHolder *inputHolder);
    ~SendDistanceTask() = default;

    void execute() override;
    void cleanup() override;
};
