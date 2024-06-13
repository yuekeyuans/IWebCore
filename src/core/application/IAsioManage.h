#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

class asio::io_context;

$PackageWebCoreBegin

class IAsioManage : public ISingletonUnit<IAsioManage>
{
public:
    IAsioManage();

public:
    asio::io_context* getMainIoContext();
};

$PackageWebCoreEnd
