#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextTomlProfileTask : public IContextTaskInterface<IContextTomlProfileTask>
{
    $AsProfile(IContextTomlProfileTask)
private:
    IContextTomlProfileTask() = default;

public:
    virtual QJsonValue config();
};

$PackageWebCoreEnd
