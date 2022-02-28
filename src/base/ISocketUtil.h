#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ISocketUtil
{
    QTcpSocket *createTcpSocket(qintptr handle);

    /// tcp 端口不可读
    void processReadError(QTcpSocket** socket);

    /// 没有找到handle
    void handleNotFoundError(QTcpSocket** socket);

    void handleInternalError(QTcpSocket** socket);

    void writeToSocket(QTcpSocket** socket, const char* content);

    /// 关闭tcp接口
    void closeTcpSocket(QTcpSocket** socket);
};

$PackageWebCoreEnd
