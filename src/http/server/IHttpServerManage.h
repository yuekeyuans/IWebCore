#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/server/IServerWare.h"
#include "IServerWare.h"

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
    QSharedPointer<IServerWare> m_server{};
};

$PackageWebCoreEnd
