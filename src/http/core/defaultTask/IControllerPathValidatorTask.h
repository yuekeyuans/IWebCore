#include "core/base/IHeaderUtil.h"
#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

class IControllerPathValidatorTask : public IInitializationTaskInterface<IControllerPathValidatorTask>
{
public:
    IControllerPathValidatorTask() = default;

public:
    virtual void task() final;
};

$PackageWebCoreEnd
