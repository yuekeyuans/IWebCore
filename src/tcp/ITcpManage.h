#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "tcp/ITcpResolverFactoryWare.h"
#include <unordered_set>

$PackageWebCoreBegin

class ITcpConnection;
class ITcpManage : public ISingletonUnit<ITcpManage>
{
public:
    ITcpManage() = default;

//public:
//    void addConnection(ITcpConnection*);
//    void removeConnection(ITcpConnection*);

public:
    void registResolverFactory(ITcpResolverFactoryWare*);
    int getResolverFactoryId(IStringView);
    ITcpResolver* createResolver(ITcpConnection&, int id);
    void destoryResolver(ITcpResolver*);

private:
    std::vector<ITcpResolverFactoryWare*> m_resolverFactories;
//    std::mutex mutex;
//    std::unordered_set<ITcpConnection*> m_connections;
};

$PackageWebCoreEnd
