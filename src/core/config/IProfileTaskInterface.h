#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IProfileManage.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IProfileTaskInterface : public ITaskWareUnit<T, enabled>
{
public:
    IProfileTaskInterface() = default;

public:
    virtual QJsonValue getContext() = 0;
    virtual QString getPath() const;

protected:
    virtual QString name() const final;
    virtual QString catagory() const final;
    virtual void task() override;
};

template<typename T, bool enabled>
QString IProfileTaskInterface<T, enabled>::getPath() const
{
    return {};
}

template<typename T, bool enabled>
QString IProfileTaskInterface<T, enabled>::name() const
{
    return typeid(T).name();
}

template<typename T, bool enabled>
QString IProfileTaskInterface<T, enabled>::catagory() const
{
    return "Context";
}

template<typename T, bool enabled>
void IProfileTaskInterface<T, enabled>::task()
{
    auto config = getContext();
    if(!config.isNull() && !config.isUndefined()){
        IProfileManage::instance()->addConfig(config, getPath());
    }
}

$PackageWebCoreEnd
