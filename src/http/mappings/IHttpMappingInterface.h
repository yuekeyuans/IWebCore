#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"
#include "http/IHttpTaskCatagory.h"
#include "http/mappings/IHttpMappingWare.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IHttpMappingInterface : public IHttpMappingWare, public ITaskWareUnit<T, IHttpTaskCatagory, enabled>, public ISingletonUnit<T>
{
public:
    IHttpMappingInterface() = default;

public:
    virtual void $task() final;

public:
    static const QString CLASS_NAME;
};

template<typename T, bool enabled>
void IHttpMappingInterface<T, enabled>::$task()
{
    if constexpr (enabled){
        IHttpManage::instance()->registMappingWare(T::instance());
    }
}

template<typename T, bool enabled>
const QString IHttpMappingInterface<T, enabled>::CLASS_NAME = IMetaUtil::getBareTypeName<T>();

$PackageWebCoreEnd
