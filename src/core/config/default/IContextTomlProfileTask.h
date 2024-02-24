#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextTomlProfileTask : public IContextTaskInterface<IContextTomlProfileTask>
{
public:
    virtual double order() const;
    virtual QJsonValue config();
};

$PackageWebCoreEnd
