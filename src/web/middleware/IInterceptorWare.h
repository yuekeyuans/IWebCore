#pragma once

#include "base/IHeaderUtil.h"
#include "IMiddleWare.h"

$PackageWebCoreBegin

class IInterceptorWare : public IMiddleWare
{
public:
    using IMiddleWare::operator();

public:
    IInterceptorWare() = default;

    virtual QString name() override = 0;
    virtual bool match(IRequest& request, IResponse& response) override = 0;
    virtual bool action(IRequest& request, IResponse& response) override = 0;
};

$PackageWebCoreEnd
