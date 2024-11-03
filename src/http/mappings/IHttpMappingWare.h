#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IHttpAction;
class IHttpMappingWare
{
public:
    IHttpMappingWare() = default;
    virtual ~IHttpMappingWare() = default;

public:
    virtual void travelPrint() const = 0;
    virtual IHttpAction* getAction(IRequest& request) const = 0;
};

$PackageWebCoreEnd
