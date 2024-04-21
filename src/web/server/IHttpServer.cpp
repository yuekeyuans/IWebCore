#include "IHttpServer.h"
#include "core/base/IConstantUtil.h"
#include "web/controller/IHttpManage.h"
#include "web/server/IHttpServerManage.h"
#include "web/node/IUrlActionNode.h"

$PackageWebCoreBegin

namespace IHttpServerHelper{
    IUrlActionNode generateUrlActionNode(IHttpMethod method, const QString& path, IHttpServer::ProcessFunctor functor);
}

IHttpServer::IHttpServer() :  QTcpServer()
{
}

bool IHttpServer::listen(const QHostAddress &address_, quint16 port_)
{
    auto newAdress = address_;
    auto newPort = port_;
    if(address_.isNull()){
        newAdress = host == "any" ? QHostAddress::Any : QHostAddress(host);
    }
    if(port_ == 0){
        newPort = port;
    }

    auto result = this->QTcpServer::listen(newAdress, newPort);
    if(result){
        QString info = QString("server started at %1:%2").arg(newAdress.toString()).arg(newPort);
        qDebug().noquote() << info;
    }else{
        QString info = QString("fail to start server at %1:%2").arg(newAdress.toString()).arg(newPort);
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

// TODO: 这个要被注销掉， 或者不从这里使用。
void IHttpServer::serveStatic(const QString &dir, const QString &prefix)
{
    IHttpManage::instance()->registerStaticFiles(dir, prefix);
}

void IHttpServer::get(const QString &path, IHttpServer::ProcessFunctor functor)
{
    serveDynamic(IHttpMethod::GET, path, functor);
}

void IHttpServer::post(const QString &path, IHttpServer::ProcessFunctor functor)
{
    serveDynamic(IHttpMethod::GET, path, functor);
}

void IHttpServer::put(const QString &path, IHttpServer::ProcessFunctor functor)
{
    serveDynamic(IHttpMethod::GET, path, functor);
}

void IHttpServer::deletes(const QString &path, IHttpServer::ProcessFunctor functor)
{
    serveDynamic(IHttpMethod::GET, path, functor);
}

void IHttpServer::patch(const QString &path, IHttpServer::ProcessFunctor functor)
{
    serveDynamic(IHttpMethod::GET, path, functor);
}

void IHttpServer::serveDynamic(IHttpMethod method, const QString &path, IHttpServer::ProcessFunctor functor)
{
    auto node = IHttpServerHelper::generateUrlActionNode(method, path, functor);
    IHttpManage::instance()->registerUrlActionNode(node);
}

void IHttpServer::incomingConnection(qintptr handle)
{
    IHttpServerManage::addSocket(handle);
}

IUrlActionNode IHttpServerHelper::generateUrlActionNode(IHttpMethod method, const QString& path, IHttpServer::ProcessFunctor functor)
{
    IUrlActionNode node;
    node.url = path;
    node.httpMethod = method;
    node.type = IUrlActionNode::Function;
    node.functionNode = IFunctionNode::createFunctionNode(functor);

    return node;
}

$PackageWebCoreEnd
