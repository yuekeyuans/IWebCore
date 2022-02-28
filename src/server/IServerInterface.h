#pragma once

#include "base/IHeaderUtil.h"

#include <QtCore>
#include <QtNetwork>

$PackageWebCoreBegin

class IServerInterface
{
public:
    IServerInterface() = default;
    virtual bool listen() = 0;
    virtual void setHost(const QString& host) = 0;
    virtual void setPort(int port) = 0;
};

$PackageWebCoreEnd
