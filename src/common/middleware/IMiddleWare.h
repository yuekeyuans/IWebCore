#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;

class IMiddleWare
{
public:
    IMiddleWare() = default;

    virtual QString name() = 0;
    virtual QString validZone(){ return ""; };  // TODO: this will be supported latter
    virtual bool match(IRequest& request, IResponse& response) = 0;
    virtual bool action(IRequest& request, IResponse& response) = 0;
};

$PackageWebCoreEnd
