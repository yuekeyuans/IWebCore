#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ISocketUtil
{
    QTcpSocket *createTcpSocket(qintptr handle);

    /// 没有找到handle
    void handleNotFoundError(QTcpSocket* socket);

    void handleInternalError(QTcpSocket* socket);

    void writeToSocket(QTcpSocket* socket, const char* content);

    void closeTcpSocket(QTcpSocket* socket);
};

$PackageWebCoreEnd
