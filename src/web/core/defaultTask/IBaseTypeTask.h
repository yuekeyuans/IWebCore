#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

// TODO: 这个改一下名字， 使用 IControllerBaseTypeTask 之类的名字

class IBaseTypeTask : public ITaskInstantUnit<IBaseTypeTask, true> 
{
public:
    IBaseTypeTask() = default;

    virtual void task() final;
}

$PackageWebCoreEnd