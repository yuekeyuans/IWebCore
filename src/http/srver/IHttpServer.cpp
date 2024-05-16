#include "IHttpServer.h"
#include "core/application/IApplicationInterface.h"
#include "core/application/IAsioApplication.h"

$PackageWebCoreBegin

IHttpServer::IHttpServer()
{

}

void IHttpServer::listen()
{
    auto application = dynamic_cast<IAsioApplication*>(IApplicationInterface::instance());
    if(!application){
        qFatal("application not supported");
        return;
    }
    asio::ip::tcp::resolver resolver(application->ioContext());
    asio::ip::tcp::endpoint endpoint =
            *resolver.resolve(ip.value().toStdString(), QString::number(port.value()).toStdString()).begin();
    m_acceptor = new asio::ip::tcp::acceptor(application->ioContext());
    m_acceptor->open(endpoint.protocol());
    m_acceptor->set_option(asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor->bind(endpoint);
    m_acceptor->listen();

    doAccept();
}

void IHttpServer::doAccept()
{
    m_acceptor->async_accept([this](std::error_code ec, asio::ip::tcp::socket socket){
        if(!m_acceptor->is_open()){
            return;
        }

        if(!ec){
            qDebug() << "accept socket";
            // TODO: write code here;
        }
        doAccept();
    });
}

$PackageWebCoreEnd
