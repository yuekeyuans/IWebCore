#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
struct IHttpControllerAction;
class IHttpMappingWare
{
public:
    IHttpMappingWare() = default;
    virtual ~IHttpMappingWare() = default;

public:
    virtual void travelPrint() = 0;
    virtual IHttpControllerAction* getUrlActionNode(IRequest& request) = 0;

};

$PackageWebCoreEnd
