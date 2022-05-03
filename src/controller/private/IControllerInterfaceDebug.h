#pragma once

#include "base/IHeaderUtil.h"
#include "test/IDebugInterface.h"

$PackageWebCoreBegin

class IControllerInterfaceDebug : public IDebugInterface
{
public:
    IControllerInterfaceDebug();

private:
    virtual QJsonObject jsonFormatedInfo() final;
};

$PackageWebCoreEnd
