#include "IHttpServer.h"
#include "http/IHttpResolverFactory.h"
#include "core/config/IProfileImport.h"

IHttpServer::IHttpServer(asio::io_context *context)
    : ITcpServer(context)
{
    $StdString ip{"/http/ip"};
    if(!ip.value().empty()){
        m_ip = *ip;
    }

    $Int port{"/http/port", -1};
    if(*port != -1){
        m_port = *port;
    }

    auto name = ISingletonUnitDetail::getInstance<IHttpResolverFactory>()->getName().m_view;
    m_resolverFactoryId = ITcpManage::instance()->getResolverFactoryId(name);
    if(m_resolverFactoryId == -1){
        qFatal("resolver factory not configed, please config resolver factory");
    }
}
