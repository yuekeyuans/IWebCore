#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskPreProcessor.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class ITaskWareUnit : public ITaskWare
{
    $AsTaskUnit(ITaskWareUnit)
    Q_DISABLE_COPY_MOVE(ITaskWareUnit)
protected:
    ITaskWareUnit() = default;
    virtual ~ITaskWareUnit() = default;

protected:
    virtual QString $name() const final;
};

template<typename T, bool enabled>
QString ITaskWareUnit<T, enabled>::$name() const
{
    return IMetaUtil::getBareTypeName<T>();
}

$UseTaskUnit(ITaskWareUnit)
{
    if constexpr (enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITaskManage::instance()->addTaskWare(ISingletonUnitDetail::getInstance<T>(nullptr));
        });
    }
}

$PackageWebCoreEnd
