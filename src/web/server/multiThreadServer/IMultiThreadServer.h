#pragma once

#include "core/base/IHeaderUtil.h"
#include "web/server/IServerInterface.h"

$PackageWebCoreBegin

class IMultiThreadServer : public IServerInterface
{
    $UseInstance(IMultiThreadServer)
public:
    IMultiThreadServer() = default;

    virtual void addSocket(qintptr handle) final;
    virtual void addSocket(QTcpSocket* socket) final;

private:
    QThreadPool m_pool;
};

$PackageWebCoreEnd
