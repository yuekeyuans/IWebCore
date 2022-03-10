#pragma once

#include "base/IHeaderUtil.h"
#include "common/middleware/IMiddleWare.h"

$PackageWebCoreBegin

class IProcessorWare : public IMiddleWare
{
public:
    IProcessorWare() = default;

    virtual QString name() override = 0;
    virtual bool match(IRequest& request, IResponse& response) override = 0;
    virtual bool action(IRequest& request, IResponse& response) override = 0;
};

$PackageWebCoreEnd
