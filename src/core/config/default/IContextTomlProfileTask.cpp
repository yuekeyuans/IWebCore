#include "IContextTomlProfileTask.h"

$PackageWebCoreBegin

double IContextTomlProfileTask::order() const
{
    return 99.0;
}

QJsonValue IContextTomlProfileTask::config()
{
    return {};
}

$PackageWebCoreEnd
