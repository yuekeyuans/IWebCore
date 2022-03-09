#pragma once

#include "base/IHeaderUtil.h"
#include "common/middleware/IInterceptorWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IPostInterceptorInterface : public IInterceptorWare
{
public:
    IPostInterceptorInterface() = default;

    virtual bool match() override = 0;
    virtual bool action(IRequest& request, IResponse& response) override = 0;
};

$PackageWebCoreEnd
