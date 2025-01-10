#include "ITcpServer.h"
#include "core/application/IApplicationInterface.h"
#include "core/application/IAsioApplication.h"
#include "core/config/IProfileImport.h"
#include "core/config/IContextManage.h"
#include "http/net/IRequest.h"
#include "http/net/IRequestManage.h"
#include "tcp/ITcpConnection.h"
#include "tcp/ITcpManage.h"

$PackageWebCoreBegin

ITcpServer::ITcpServer(asio::io_context* context)
    : m_context(context)
{
    if(context == nullptr){
        auto application = dynamic_cast<IAsioApplication*>(IApplicationInterface::instance());
        if(!application){
            qFatal("application not supported");
            return;
        }
        m_context = &application->ioContext();
    }

    m_acceptor = new asio::ip::tcp::acceptor(*m_context);
}

ITcpServer::~ITcpServer()
{
    if(m_acceptor){
        if(m_acceptor->is_open()){
            m_acceptor->close();
        }

        delete m_acceptor;
        m_acceptor = nullptr;
    }
}

void ITcpServer::listen()
{
    if(m_acceptor->is_open()){
        qFatal("server started already");
    }

    asio::ip::tcp::resolver resolver(*m_context);
    asio::ip::tcp::endpoint endpoint = *resolver.resolve(
                ip.value().toStdString(),
                QString::number(port.value()).toStdString()).begin();
    m_acceptor->open(endpoint.protocol());
    m_acceptor->set_option(asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor->bind(endpoint);
    m_acceptor->listen();
    doAccept();

    IContextManage::instance()->addConfig(IJson(ip.value().toStdString()), "/runtime/ip");
    IContextManage::instance()->addConfig(IJson(*port), "/runtime/port");
    qDebug() << "server started, listen at " << *ip + ":" + QString::number(*port);
}

void ITcpServer::doAccept()
{
    m_acceptor->async_accept([this](std::error_code ec, asio::ip::tcp::socket socket){
        if(!m_acceptor->is_open()){
            return;
        }

        if(!ec){
            $Int m_timeout{"/http/readTimeOut"};
            socket.set_option(asio::detail::socket_option::integer<SOL_SOCKET, SO_RCVTIMEO>{ m_timeout.value() });
            auto connection = new ITcpConnection(std::move(socket), m_resolverFactoryId);
            ITcpManage::instance()->addConnection(connection);
        }
        doAccept();
    });
}

$PackageWebCoreEnd
