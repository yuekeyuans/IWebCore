#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IProfileTaskInterface.h"

$PackageWebCoreBegin

class IHttpDefaultProfileTask : public IProfileTaskInterface<IHttpDefaultProfileTask>
{
public:
    IHttpDefaultProfileTask() = default;

public:
    virtual double order() const final;
    virtual IJson config() final;
};

$PackageWebCoreEnd
