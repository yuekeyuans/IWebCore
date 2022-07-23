#include "ISocketUtil.h"

$PackageWebCoreBegin

QTcpSocket *ISocketUtil::createTcpSocket(qintptr handle)
{
    auto socket = new QTcpSocket;
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    socket->setSocketDescriptor(handle);
    return socket;
}

void ISocketUtil::handleNotFoundError(QTcpSocket *socket)
{
    static const char* content = "HTTP/1.1 404 NOT FOUND\r\nContent-Type:text/plain\r\nContent-Length: 14\r\n\r\nfile not found";
    writeToSocket(socket, content);
}

void ISocketUtil::writeToSocket(QTcpSocket *socket, const char *content)
{
    socket->write(content);
}

void ISocketUtil::handleInternalError(QTcpSocket *socket)
{
    // TODO:
    handleNotFoundError(socket);
}

void ISocketUtil::closeTcpSocket(QTcpSocket *socket)
{
//    static QAtomicInt cnt{0};
//    qDebug() << "socket closed" << cnt ++;
    if(socket != nullptr && socket->isOpen()){
        socket->close();
    }
}

$PackageWebCoreEnd
