#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

class IBaseTypeTask : public ITaskInstantUnit<IBaseTypeTask, true> 
{
public:
    IBaseTypeTask() = default;

    virtual void task() final;
}

$PackageWebCoreEnd