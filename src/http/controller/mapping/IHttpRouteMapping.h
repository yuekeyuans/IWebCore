// TODO: 之后文件夹应该被重构
#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/IHttpMappingInterface.h"

$PackageWebCoreBegin

class IHttpRouteMapping : public IHttpMappingInterface<IHttpRouteMapping>
{
public:
    IHttpRouteMapping() = default;
};

$PackageWebCoreEnd
