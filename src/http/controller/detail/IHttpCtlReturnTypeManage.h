#pragma once

#include "core/unit/ISingletonUnit.h"
#include "http/controller/detail/IHttpControllerActionNode.h"

$PackageWebCoreBegin

class IHttpCtlReturnTypeManage : public ISingletonUnit<IHttpCtlReturnTypeManage>
{
public:
    IHttpCtlReturnTypeManage();

public:
    IHttpControllerActionNode::ReturnType parseReturnType(const IHttpControllerActionNode& node);
    bool isReturnTypeValid(const IHttpControllerActionNode& node);
};

$PackageWebCoreEnd
