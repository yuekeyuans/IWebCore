#include "ISocketUtil.h"

$PackageWebCoreBegin

QTcpSocket *ISocketUtil::createTcpSocket(qintptr handle)
{
    auto socket = new QTcpSocket;
    socket->setSocketDescriptor(handle);
    return socket;
}

void ISocketUtil::processReadError(QTcpSocket **socket)
{
    closeTcpSocket(socket);
}

void ISocketUtil::handleNotFoundError(QTcpSocket **socket)
{
    static const char* content = "HTTP/1.1 404 NOT FOUND\r\nContent-Type:text/plain\r\nContent-Length: 14\r\n\r\nfile not found";
    writeToSocket(socket, content);
    closeTcpSocket(socket);
}

void ISocketUtil::writeToSocket(QTcpSocket **socket, const char *content)
{
    (*socket)->write(content);
}

void ISocketUtil::handleInternalError(QTcpSocket **socket)
{
    // TODO:
    handleNotFoundError(socket);
}

void ISocketUtil::closeTcpSocket(QTcpSocket *socket)
{
    qDebug() << "CLOSE TCP SOCKET";
    if(socket != nullptr && socket->isOpen()){
        socket->close();
    }
}

 use ** to guard that the caller`s socket set to nullptr;
void ISocketUtil::closeTcpSocket(QTcpSocket **socket)
{
    if(*socket != nullptr){
        if((*socket)->isWritable()){
            (*socket)->flush();
        }
        (*socket)->close();
        delete (*socket);
        *socket = nullptr;
    }
}


$PackageWebCoreEnd
