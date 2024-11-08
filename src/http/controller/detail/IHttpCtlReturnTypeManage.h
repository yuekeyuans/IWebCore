#pragma once

#include "core/unit/ISingletonUnit.h"
#include "http/controller/detail/IHttpControllerAction.h"

$PackageWebCoreBegin

class IHttpCtlReturnTypeManage : public ISingletonUnit<IHttpCtlReturnTypeManage>
{
public:
    IHttpCtlReturnTypeManage();

public:
//    IHttpControllerAction::ReturnType parseReturnType(const IHttpControllerAction& node);
    bool isReturnTypeValid(const IHttpControllerAction& node);
};

$PackageWebCoreEnd
