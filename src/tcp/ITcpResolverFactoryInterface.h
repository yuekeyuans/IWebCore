#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "ITcpResolverFactoryWare.h"
#include "tcp/ITcpManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ITcpResolverFactoryInterface : public ITcpResolverFactoryWare, public ITaskInstantUnit<T, enabled>
{
public:
    virtual void $task() final;
};

template<typename T, bool enabled>
void ITcpResolverFactoryInterface<T, enabled>::$task()
{
    if  (enabled){
        ITcpManage::instance()->registResolverFactory(ISingletonUnitDetail::getInstance<T>());
    }
}

$PackageWebCoreEnd
