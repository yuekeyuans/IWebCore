#pragma once

#include "core/unit/ISingletonUnit.h"
#include "http/controller/detail/IHttpRouteLeaf.h"

$PackageWebCoreBegin

class IHttpCtlReturnTypeManage : public ISingletonUnit<IHttpCtlReturnTypeManage>
{
public:
    IHttpCtlReturnTypeManage();

public:
    IHttpRouteLeaf::ReturnType parseReturnType(const IHttpRouteLeaf& node);
    bool isReturnTypeValid(const IHttpRouteLeaf& node);
};

$PackageWebCoreEnd
