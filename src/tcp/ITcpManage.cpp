#include "ITcpManage.h"
#include "tcp/ITcpConnection.h"

$PackageWebCoreBegin

//void ITcpManage::addConnection(ITcpConnection * conn)
//{
//    Q_UNUSED(conn)
////    std::lock_guard lock(mutex);
////    m_connections.emplace(conn);
//}

//void ITcpManage::removeConnection(ITcpConnection *conn)
//{
//    Q_UNUSED(conn)
////    {
////        std::lock_guard lock(mutex);
////        m_connections.erase(conn);
////    }
////    delete conn;
//}

void ITcpManage::registResolverFactory(ITcpResolverFactoryWare * ware)
{
    m_resolverFactories.push_back(ware);
}

int ITcpManage::getResolverFactoryId(IStringView data)
{
    for(std::size_t i=0; i<m_resolverFactories.size(); i++){
        if(m_resolverFactories[i]->getName().m_view == data){
            return static_cast<int>(i);
        }
    }
    return -1;
}

ITcpResolver *ITcpManage::createResolver(ITcpConnection & connection, int id)
{
    return m_resolverFactories[id]->createResolver(connection, id);
}

void ITcpManage::destoryResolver(ITcpResolver * resolver)
{
    return m_resolverFactories[resolver->m_resolverFactoryId]->destroyResolver(resolver);
}

void ITcpManage::registIpFilterWare(ITcpSocketFilterWare *ware)
{
    m_ipFilterWare.push_back(ware);
}

std::vector<ITcpSocketFilterWare *> ITcpManage::getIpFilterWares()
{
    return m_ipFilterWare;
}

$PackageWebCoreEnd
