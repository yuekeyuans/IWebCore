#include "IHttpServer.h"
#include "http/IHttpResolverFactory.h"

IHttpServer::IHttpServer(asio::io_context *context)
    : ITcpServer(context)
{
    auto name = ISingletonUnitDetail::getInstance<IHttpResolverFactory>()->getName().m_view;
    m_resolverFactoryId = ITcpManage::instance()->getResolverFactoryId(name);
    if(m_resolverFactoryId == -1){
        qFatal("resolver factory not configed, please config resolver factory");
    }
}
