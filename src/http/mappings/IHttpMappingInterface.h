#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"
#include "http/IHttpControllerTaskCatagory.h"
#include "http/mappings/IHttpMappingWare.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IHttpMappingInterface : public IHttpMappingWare, public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IHttpMappingInterface() = default;

public:
    virtual QString $name() const final;
    virtual const char* $catagory() const final;
    virtual void $task() final;

public:
    virtual void travelPrint() const = 0;
    virtual IHttpAction* getActions(IRequest &request) const = 0;
};

template<typename T, bool enabled>
QString IHttpMappingInterface<T, enabled>::$name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, bool enabled>
const char *IHttpMappingInterface<T, enabled>::$catagory() const
{
    return IHttpControllerTaskCatagory::CATAGORY;
}

template<typename T, bool enabled>
void IHttpMappingInterface<T, enabled>::$task()
{
    if constexpr (enabled){
        IHttpManage::instance()->registMappingWare(T::instance());
    }
}

$PackageWebCoreEnd
