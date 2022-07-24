#pragma once

#include "base/IHeaderUtil.h"
#include "IServerInterface.h"

$PackageWebCoreBegin

class IHttpServerManage
{
    $UseInstance(IHttpServerManage)
private:
    IHttpServerManage();

public:
    static void addSocket(qintptr handle);
    static void addSocket(QTcpSocket* socket);

private:
    QSharedPointer<IServerInterface> m_server;
};

$PackageWebCoreEnd
