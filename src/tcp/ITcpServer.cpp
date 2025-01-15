#include "ITcpServer.h"
#include "core/application/IApplicationInterface.h"
#include "core/application/IAsioApplication.h"
#include "core/config/IProfileImport.h"
#include "core/config/IContextManage.h"
#include "http/IRequest.h"
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

    m_ip = *$StdString{"/tcp/ip", "0.0.0.0"};
    m_port = *$Int{"/tcp/port", 8550};
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
    loadResolverFactory();

    asio::ip::tcp::resolver resolver(*m_context);
    asio::ip::tcp::endpoint endpoint = *resolver.resolve(
                m_ip, std::to_string(m_port)).begin();
    m_acceptor->open(endpoint.protocol());
    m_acceptor->set_option(asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor->bind(endpoint);
    m_acceptor->listen();
    doAccept();

    IContextManage::instance()->addConfig(IJson(m_ip), "/runtime/ip");
    IContextManage::instance()->addConfig(IJson(m_port), "/runtime/port");
    qDebug() << "server started, listen at " << QString::fromStdString(m_ip) + ":" + QString::number(m_port);
}

void ITcpServer::loadResolverFactory()
{
    if(m_resolverFactoryId >= 0){
        return;
    }
    $StdString factory{"/tcp/resolverFactory"};
    IString data(*factory);
    m_resolverFactoryId = ITcpManage::instance()->getResolverFactoryId(data.m_view);
    if(m_resolverFactoryId == -1){
        qFatal("resolver factory not configed, please config resolver factory");
    }
}

void ITcpServer::doAccept()
{
    m_acceptor->async_accept([this](std::error_code ec, asio::ip::tcp::socket socket){
        if(!m_acceptor->is_open()){
            return;
        }

        if(!ec){
            $Int m_timeout{"/http/readTimeOut"};
            socket.set_option(asio::detail::socket_option::integer<SOL_SOCKET, SO_RCVTIMEO>{ *m_timeout });
            auto connection = new ITcpConnection(std::move(socket), m_resolverFactoryId);
        }
        doAccept();
    });
}

$PackageWebCoreEnd
