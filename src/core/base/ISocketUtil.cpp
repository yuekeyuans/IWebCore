#include "ISocketUtil.h"

$PackageWebCoreBegin

QTcpSocket *ISocketUtil::createTcpSocket(qintptr handle)
{
    auto socket = new QTcpSocket;
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    socket->setSocketDescriptor(handle);
    return socket;
}

void ISocketUtil::writeToSocket(QTcpSocket *socket, const char *content)
{
    socket->write(content);
}

void ISocketUtil::closeTcpSocket(QTcpSocket *socket)
{
    socket->close();
}

$PackageWebCoreEnd
