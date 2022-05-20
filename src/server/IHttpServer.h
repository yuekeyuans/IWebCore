#pragma once
#include "base/IMetaUtil.h"
#include "core/configuration/configuration"
#include "server/IHttpServerManage.h"

$PackageWebCoreBegin

class IHttpServer : public QTcpServer
{
    Q_GADGET
    $UseInstance(IHttpServer)
    $UseConfig(IHttpSever)
public:
    IHttpServer();
    bool listen();
    void setHost(const QString &host);
    void setPort(int port);

private:
    virtual void incomingConnection(qintptr handle) final;

private:
    $OptionWireDeclare(QString, host, server.host)
    QString host = "127.0.0.1";

    $OptionWireDeclare(int, port, server.port)
    int port = 8088;

private:
    IHttpServerManage m_serverManage;
};

$PackageWebCoreEnd
