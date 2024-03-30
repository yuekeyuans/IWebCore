#pragma once

#include "core/base/IConstantUtil.h"
#include "core/config/IConfigPreProcessor.h"
#include "core/config/IProfileImport.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"

$PackageWebCoreBegin

class IHttpServer : public QTcpServer
{
    Q_GADGET
public:
    using ProcessFunctor = std::function<void(const IRequest& req, IResponse& resp)>;

public:
    IHttpServer();
    bool listen(const QHostAddress &address = QHostAddress::Null, quint16 port = 0);
    void setHost(const QString &host);
    void setPort(int port);

public:
    void serveStatic(const QString& dir, const QString& prefix="/");

    void get(const QString& path, ProcessFunctor functor);
    void post(const QString& path, ProcessFunctor functor);
    void put(const QString& path, ProcessFunctor functor);
    void deletes(const QString& path, ProcessFunctor functor);
    void patch(const QString& path, ProcessFunctor functor);
    void serveDynamic(IHttpMethod method, const QString& path, ProcessFunctor);

private:
    virtual void incomingConnection(qintptr handle) final;

private:
    $QString host{"http.ip"};
    $UShort port{"http.port"};
};

$PackageWebCoreEnd
