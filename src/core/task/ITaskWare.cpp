#include "ITaskWare.h"
#include "core/configuration/IContextManage.h"

$PackageWebCoreBegin

bool ITaskWare::isTaskDefaultEnabled() const
{
    return true;
}

bool ITaskWare::isTaskEnabled() const
{
    bool ok;

    auto path = QString("TASK_ENABLE_STATE_").append(catagory()).append("_").append(name());
    auto value = IContextManage::getSystemValue(path, &ok);
    if(!ok){
        return this->isTaskDefaultEnabled();
    }

    return value.toBool();
}

$PackageWebCoreEnd
