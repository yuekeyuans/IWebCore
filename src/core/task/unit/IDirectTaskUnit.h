#pragma once

#include "core/task/ITaskManage.h"
#include "core/task/ITaskWare.h"
#include "core/base/IHeaderUtil.h"
#include "core/base/ITraitHelper.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IDirectTaskUnit : public ITaskWare
{
    $AsTaskUnit(IDirectTaskUnit)
public:
    IDirectTaskUnit() = default;

public:
    virtual void task() = 0;

public:
    virtual QString name() const override;
    virtual QString catagory() const override;
};

template<typename T, bool enabled>
QString IDirectTaskUnit<T, enabled>::name() const
{
    return "hello";
}

template<typename T, bool enabled>
QString IDirectTaskUnit<T, enabled>::catagory() const
{
    return "IDirectTaskUnit";
}

$UseTaskUnit(IDirectTaskUnit)
{
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, []{
            T{}.task();
        });
    }
}

$PackageWebCoreEnd
