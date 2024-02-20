#include "ITaskWare.h"
#include "core/config/IContextImport.h"

$PackageWebCoreBegin

bool ITaskWare::isTaskDefaultEnabled() const
{
    return true;
}

bool ITaskWare::isTaskEnabled() const
{
    auto path = QString("TASK_ENABLE_STATE_").append(catagory()).append("_").append(name());
    $ContextBool value{path};
    return value.isFound() ? value : this->isTaskDefaultEnabled();
}

$PackageWebCoreEnd
