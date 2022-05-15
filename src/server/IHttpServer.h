#pragma once
#include "server/IServerInterface.h"
#include "configuration/configuration"
#include "base/IMetaUtil.h"

$PackageWebCoreBegin

class IHttpServer : public IServerInterface, public QTcpServer
{
    Q_GADGET
    $UseInstance(IHttpServer)
    $UseConfig(IHttpSever)
public:
    IHttpServer();
    virtual bool listen() final;
    virtual void setHost(const QString &host) final;
    virtual void setPort(int port) final;

private:
    virtual void incomingConnection(qintptr handle) final;

private:
    $OptionWireDeclare(QString, host, server.host)
    QString host = "127.0.0.1";

    $OptionWireDeclare(int, port, server.port)
    int port = 8088;
};

$PackageWebCoreEnd
