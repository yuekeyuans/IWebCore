#include "core/util/IHeaderUtil.h"
#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

class IHttpPathValidatorsTask : public IInitializationTaskInterface<IHttpPathValidatorsTask>
{
public:
    IHttpPathValidatorsTask() = default;

public:
    virtual void $task() final;
};

$PackageWebCoreEnd
