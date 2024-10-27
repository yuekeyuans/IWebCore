#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IHttpRouteLeaf;
class IHttpMappingWare
{
public:
    IHttpMappingWare() = default;
    virtual ~IHttpMappingWare() = default;

public:
    virtual void travelPrint() = 0;
    virtual IHttpRouteLeaf* getUrlActionNode(IRequest& request) = 0;

};

$PackageWebCoreEnd
