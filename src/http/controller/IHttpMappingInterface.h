#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"
#include "http/IHttpControllerTaskCatagory.h"

$PackageWebCoreBegin

template<typename T, bool enabled>
class IHttpMappingInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IHttpMappingInterface();

public:
    virtual QString $name() const final;
    virtual const char* $catagory() const final;
    virtual void $task() final;
};

template<typename T, bool enabled>
QString IHttpMappingInterface::$name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, bool enabled>
const char *IHttpMappingInterface::$catagory() const
{
    return IHttpControllerTaskCatagory::CATAGORY;
}

template<typename T, bool enabled>
void IHttpMappingInterface::$task()
{
    if constexpr (enabled){
        // TODO: 注册
    }
}

$PackageWebCoreEnd
