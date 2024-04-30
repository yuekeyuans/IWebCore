#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ISocketUtil
{
    QTcpSocket *createTcpSocket(qintptr handle);

    void writeToSocket(QTcpSocket* socket, const char* content);

    void closeTcpSocket(QTcpSocket* socket);
}

$PackageWebCoreEnd
