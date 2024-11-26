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
    auto path = QString("/TASK_ENABLE_STATE_")
            .append(QString::fromStdString($catagory()))
            .append("_")
            .append(QString::fromStdString($name()));

    $ContextBool value{path.toStdString(), this->$isTaskDefaultEnabled()};
    return *value;
}

$PackageWebCoreEnd
