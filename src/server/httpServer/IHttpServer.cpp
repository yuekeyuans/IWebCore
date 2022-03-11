#include "IHttpServer.h"
#include "server/httpServer/IHttpServerManage.h"

$PackageWebCoreBegin

IHttpServer::IHttpServer() : IServerInterface(), QTcpServer()
{
    $ConstructConfig()
}

bool IHttpServer::listen()
{
    QHostAddress address = host == "any" ? QHostAddress::Any : QHostAddress(host);
    auto result = QTcpServer::listen(address, port);
    if(result){
        QString info = QString("server started at %1:%2").arg(address.toString()).arg(port);
        qDebug().noquote() << info;
    }else{
        QString info = QString("fail to start server at %1:%2").arg(address.toString()).arg(port);
        qDebug().noquote() << info;
    }

    return result;
}

void IHttpServer::setHost(const QString &host)
{
    this->host = host;
}

void IHttpServer::setPort(int port)
{
    this->port = port;
}

// TODO: 为了解决 C10K 问题，有一个简便的权宜之计, 就是在这里获取到 handle 之后，将 handle 放置在
// 自定义的 事件循环里面，在 Linux 下面是 epoll, 在windows 下面是 IOCP.
void IHttpServer::incomingConnection(qintptr handle)
{
    IHttpServerManage::addSocket(handle);
}

$PackageWebCoreEnd
