#include "ITaskWare.h"
#include "core/config/IContextImport.h"

$PackageWebCoreBegin

bool ITaskWare::$isTaskDefaultEnabled() const
{
    return true;
}

// TODO: 检查一下这个可起效了
bool ITaskWare::isTaskEnabled() const
{
    auto path = std::string("/TASK_ENABLE_STATE_")+ $catagory() + "_" + $name();
    $ContextBool value{path, this->$isTaskDefaultEnabled()};
    return *value;
}

$PackageWebCoreEnd
