#pragma once

#include "base/IHeaderUtil.h"
#include "server/IServerInterface.h"

$PackageWebCoreBegin

class IMultiThreadServer : public IServerInterface
{
    $UseInstance(IMultiThreadServer)
public:
    IMultiThreadServer() = default;

    virtual void addSocket(qintptr handle) final;

private:
    QThreadPool m_pool;
};

$PackageWebCoreEnd
