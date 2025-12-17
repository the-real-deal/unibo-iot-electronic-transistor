#include "Context.hpp"

class HangarState
{
private:
protected:
    Context *context;

public:
    HangarState();
    ~HangarState();
    void setContext(Context *ctx)
    {
        this->context = ctx;
    }
};