#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IInitializationTaskInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IInitializationTaskInterface() = default;

public:
    virtual void $task() = 0;

protected:
    virtual QString $name() const final;
    virtual const char* $catagory() const final;
};

template<typename T, bool enabled>
QString IInitializationTaskInterface<T, enabled>::$name() const
{
    return IMetaUtil::getBareTypeName<T>();
}

template<typename T, bool enabled>
const char* IInitializationTaskInterface<T, enabled>::$catagory() const
{
    return "Initialization";
}

$PackageWebCoreEnd
