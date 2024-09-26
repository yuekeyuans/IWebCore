#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IProfileManage.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IProfileTaskInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IProfileTaskInterface() = default;

public:
    virtual IJson config() = 0;
    virtual std::string path() const;

protected:
    virtual QString name() const final;
    virtual QString catagory() const final;
    virtual void task() final;
};

template<typename T, bool enabled>
std::string IProfileTaskInterface<T, enabled>::path() const
{
    return {};
}

template<typename T, bool enabled>
QString IProfileTaskInterface<T, enabled>::name() const
{
    return IMetaUtil::getBareTypeName<T>();
}

template<typename T, bool enabled>
QString IProfileTaskInterface<T, enabled>::catagory() const
{
    return "Config";
}

template<typename T, bool enabled>
void IProfileTaskInterface<T, enabled>::task()
{
    auto value = config();
    if(!value.is_null()){
        IProfileManage::instance()->addConfig(value, path());
    }
}

$PackageWebCoreEnd
