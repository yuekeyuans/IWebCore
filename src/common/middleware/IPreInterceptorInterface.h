#pragma once

#include "base/IHeaderUtil.h"
#include "common/middleware/IInterceptorWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IPreInterceptorInterface : public IInterceptorWare
{
public:
    IPreInterceptorInterface() = default;

    virtual bool match(IRequest& request, IResponse& response) override = 0;
    virtual bool action(IRequest& request, IResponse& response) override = 0;
};

$PackageWebCoreEnd
