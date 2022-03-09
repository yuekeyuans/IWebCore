#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;

class IMiddleWare
{
public:
    IMiddleWare() = default;

    virtual bool match() = 0;
    virtual bool action(IRequest& request, IResponse& response) = 0;
};

$PackageWebCoreEnd
