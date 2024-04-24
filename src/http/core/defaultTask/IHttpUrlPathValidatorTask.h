#include "core/base/IHeaderUtil.h"
#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

class IHttpUrlPathValidatorTask : public IInitializationTaskInterface<IHttpUrlPathValidatorTask>
{
public:
    IHttpUrlPathValidatorTask() = default;

public:
    virtual void task() final;
};

$PackageWebCoreEnd
