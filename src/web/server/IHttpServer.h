#pragma once

#include "IHttpServerManage.h"
#include "base/IMetaUtil.h"
#include "core/configuration/configuration"
#include "web/biscuits/IHttpMethod.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"

$PackageWebCoreBegin

class IHttpServer : public QTcpServer
{
    Q_GADGET
    $UseInstance(IHttpServer)
    $UseConfig(IHttpSever)

public:
    using ProcessFunctor = std::function<void(const IRequest& req, IResponse& resp)>;

public:
    IHttpServer();
    bool listen();
    void setHost(const QString &host);
    void setPort(int port);

public:
    void serveStatic(const QString& path, const QString& prefix="/");

    void get(const QString& path, ProcessFunctor functor);
    void post(const QString& path, ProcessFunctor functor);
    void put(const QString& path, ProcessFunctor functor);
    void deletes(const QString& path, ProcessFunctor functor);
    void patch(const QString& path, ProcessFunctor functor);

    void serve(IHttpMethod method, const QString& path, ProcessFunctor);

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
