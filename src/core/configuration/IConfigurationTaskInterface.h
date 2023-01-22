#pragma once

#include "base/IHeaderUtil.h"
#include "core/unit/IRegisterInstanceUnit.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "base/IMetaUtil.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IConfigurationTaskInterface : public ITaskWare, public IRegisterInstanceUnit<T, enabled>
{
public:
    IConfigurationTaskInterface() = default;

public:
    virtual void registerToBase() final;

protected:
    virtual QString name() const override;
    virtual QString catagory() const final;
};

template<typename T, bool enabled>
void IConfigurationTaskInterface<T, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}

template<typename T, bool enabled>
QString IConfigurationTaskInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
QString IConfigurationTaskInterface<T, enabled>::catagory() const
{
    return "Configuration";
}


$PackageWebCoreEnd
