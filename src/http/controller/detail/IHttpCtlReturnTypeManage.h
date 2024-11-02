#pragma once

#include "core/unit/ISingletonUnit.h"
#include "http/controller/detail/IHttpAction.h"

$PackageWebCoreBegin

class IHttpCtlReturnTypeManage : public ISingletonUnit<IHttpCtlReturnTypeManage>
{
public:
    IHttpCtlReturnTypeManage();

public:
    IHttpAction::ReturnType parseReturnType(const IHttpAction& node);
    bool isReturnTypeValid(const IHttpAction& node);
};

$PackageWebCoreEnd
