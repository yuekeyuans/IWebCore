#pragma once
#include "base/IHeaderUtil.h"


$PackageWebCoreBegin

class IRequest;
class IResponse;
class IRequestPreInterceptorInterface
{
public:
    virtual bool match(const IRequest& request) = 0;
    virtual void intercept(IRequest& request, IResponse& response) = 0;
};

$PackageWebCoreEnd
