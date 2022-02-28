#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin


class IResponse;
class IRequest;
class IResponsePostInterceptInterface
{
public:
    IResponsePostInterceptInterface();
    bool match(IRequest& request, const IResponse&);
    void intercept(IRequest& request, IResponse& response);
};


$PackageWebCoreEnd
