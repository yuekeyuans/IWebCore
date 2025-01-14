#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "core/util/IMemoryObjectPool.h"
#include "ITcpResolverFactoryWare.h"
#include "tcp/ITcpManage.h"

$PackageWebCoreBegin

template<typename T, typename U, bool enabled=true>
class ITcpResolverFactoryInterface : public ITcpResolverFactoryWare, public ITaskInstantUnit<T, enabled>
{
public:
    virtual void $task() final;
    virtual ITcpResolver* createResolver(ITcpConnection&, int) final;
    virtual void destroyResolver(ITcpResolver*) final;

private:
    IMemoryObjectPool<U> m_pool{};
};

template<typename T, typename U, bool enabled>
void ITcpResolverFactoryInterface<T, U, enabled>::$task()
{
    if  (enabled){
        ITcpManage::instance()->registResolverFactory(ISingletonUnitDetail::getInstance<T>());
    }
}

template<typename T, typename U, bool enabled>
ITcpResolver *ITcpResolverFactoryInterface<T, U, enabled>::createResolver(ITcpConnection &connection, int id)
{
    return m_pool.allocate(connection, id);
}

template<typename T, typename U, bool enabled>
void ITcpResolverFactoryInterface<T, U, enabled>::destroyResolver(ITcpResolver *resolver)
{
    return m_pool.deallocate(dynamic_cast<U*>(resolver));
}

$PackageWebCoreEnd
