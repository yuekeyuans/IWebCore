#include "IHttpServer.h"
#include "core/application/IApplicationInterface.h"
#include "core/application/IAsioApplication.h"
#include "http/net/IRequest.h"
#include "http/net/IRequestManage.h"
#include "http/net/server/ITcpResolverManage.h"
#include "http/net/server/ITcpConnection.h"
#include "http/net/server/ITcpConnectionManage.h"

$PackageWebCoreBegin

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
            $Int m_timeout{"http.readTimeOut"};
            socket.set_option(asio::detail::socket_option::integer<SOL_SOCKET, SO_RCVTIMEO>{ m_timeout.value() });
            auto connection = new ITcpConnection(std::move(socket));
            ITcpConnectionManage::instance()->addTcpConnection(connection);
        }
        doAccept();
    });
}

$PackageWebCoreEnd
