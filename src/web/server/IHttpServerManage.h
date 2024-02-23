#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "IServerInterface.h"

$PackageWebCoreBegin

extern const char* MasterServer;

class IHttpServerManage : public ISingletonUnit<IHttpServerManage>
{
public:
    IHttpServerManage();

public:
    static void addSocket(qintptr handle);
    static void addSocket(QTcpSocket* socket);

private:
    QSharedPointer<IServerInterface> m_server;
};

$PackageWebCoreEnd
