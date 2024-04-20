#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IServerWare
{
public:
    IServerWare() = default;
    virtual ~IServerWare() = default;

    virtual void addSocket(qintptr handle) =0;
    virtual void addSocket(QTcpSocket* socket) = 0;
};

$PackageWebCoreEnd
