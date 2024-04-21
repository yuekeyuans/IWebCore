#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IProfileTaskInterface.h"

$PackageWebCoreBegin

class IWebDefaultProfileTask : public IProfileTaskInterface<IWebDefaultProfileTask>
{
public:
    IWebDefaultProfileTask() = default;

public:
    virtual double order() const final;
    virtual QJsonValue config() final;
};

$PackageWebCoreEnd
