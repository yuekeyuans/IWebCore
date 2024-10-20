#pragma once

#include "core/unit/ISingletonUnit.h"
#include "http/controller/detail/IHttpRouteLeafNode.h"

$PackageWebCoreBegin

class IHttpCtlReturnTypeManage : public ISingletonUnit<IHttpCtlReturnTypeManage>
{
public:
    IHttpCtlReturnTypeManage();

public:
    IHttpRouteLeafNode::ReturnType parseReturnType(const IHttpRouteLeafNode& node);
    bool isReturnTypeValid(const IHttpRouteLeafNode& node);
};

$PackageWebCoreEnd
