﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/util/IMetaUtil.h"
#include "core/config/IContextManage.h"
#include "core/task/unit/ITaskWareUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IContextTaskInterface : public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IContextTaskInterface() = default;

public:
    virtual IJson config() = 0;
    virtual std::string path() const;

protected:
    virtual QString name() const final;
    virtual QString catagory() const final;
    virtual void task() final;
};

template<typename T, bool enabled>
std::string IContextTaskInterface<T, enabled>::path() const
{
    return {};
}

template<typename T, bool enabled>
QString IContextTaskInterface<T, enabled>::name() const
{
    return IMetaUtil::getBareTypeName<T>();
}

template<typename T, bool enabled>
QString IContextTaskInterface<T, enabled>::catagory() const
{
    return "Config";
}

template<typename T, bool enabled>
void IContextTaskInterface<T, enabled>::task()
{
    IJson value = config();
    if(!value.is_null()){
        IContextManage::instance()->addConfig(value, path());
    }
}

$PackageWebCoreEnd
