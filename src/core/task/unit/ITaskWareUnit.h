#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskPreProcessor.h"
#include "core/unit/ISingletonUnit.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

template<typename T, typename Catagory, bool enabled=true>
class ITaskWareUnit : public ITaskWare, public IClassNameUnit<T>
{
    $AsTaskUnit(ITaskWareUnit)
    Q_DISABLE_COPY_MOVE(ITaskWareUnit)
protected:
    ITaskWareUnit() = default;
    virtual ~ITaskWareUnit() = default;

protected:
    virtual const std::string& $name() const final;
    virtual const std::string& $catagory() const final;
};

template<typename T, typename Catagory, bool enabled>
const std::string& ITaskWareUnit<T, Catagory, enabled>::$name() const
{
    return ITaskWareUnit::CLASS_NAME;
}

template<typename T, typename Catagory, bool enabled>
const std::string& ITaskWareUnit<T, Catagory, enabled>::$catagory() const
{
    return Catagory::CLASS_NAME;
}

$UseTaskUnit2(ITaskWareUnit)
{
    if constexpr (enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::instance()->addTaskWare(ISingletonUnitDetail::getInstance<T>(nullptr));
        });
    }
}

$PackageWebCoreEnd
