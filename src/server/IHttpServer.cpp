#include "IHttpServer.h"
#include "server/IHttpServerManage.h"

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

void IHttpServer::incomingConnection(qintptr handle)
{
    IHttpServerManage::addSocket(handle);
}

$PackageWebCoreEnd
