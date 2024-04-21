#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/middleware/IMiddleWare.h"

$PackageWebCoreBegin

class IProcessorWare : public IMiddleWare
{
public:
    using IMiddleWare::operator();

public:
    IProcessorWare() = default;

    virtual QString name() override = 0;
    virtual bool match(IRequest& request, IResponse& response) override = 0;
    virtual bool action(IRequest& request, IResponse& response) override = 0;
};

$PackageWebCoreEnd
