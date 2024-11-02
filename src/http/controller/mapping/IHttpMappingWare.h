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
    virtual void travelPrint() = 0;
    virtual IHttpAction* getUrlActionNode(IRequest& request) = 0;

};

$PackageWebCoreEnd
