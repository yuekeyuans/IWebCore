#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IContextManage.h"
#include "core/config/IContextPreProcessor.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IContextTaskInterface : public ITaskWareUnit<T, enabled>
{
public:
    IContextTaskInterface() = default;

public:
    virtual QJsonValue getContext() = 0;
    virtual QString getPath() const;

protected:
    virtual QString name() const final;
    virtual QString catagory() const final;
    virtual void task() override;
};

template<typename T, bool enabled>
QString IContextTaskInterface<T, enabled>::getPath() const
{
    return {};
}

template<typename T, bool enabled>
QString IContextTaskInterface<T, enabled>::name() const
{
    return typeid(T).name();
}

template<typename T, bool enabled>
QString IContextTaskInterface<T, enabled>::catagory() const
{
    return "Context";
}

template<typename T, bool enabled>
void IContextTaskInterface<T, enabled>::task()
{
    auto config = getContext();
    if(!config.isNull() && !config.isUndefined()){
        IContextManage::instance()->addConfig(config, getPath());
    }
}

$PackageWebCoreEnd
