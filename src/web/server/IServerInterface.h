#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IServerInterface
{
public:
    IServerInterface() = default;
    virtual ~IServerInterface() = default;

    virtual void addSocket(qintptr handle) =0;
    virtual void addSocket(QTcpSocket* socket) = 0;
};

$PackageWebCoreEnd
