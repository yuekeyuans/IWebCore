#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"
#include "core/task/ITaskPreProcessor.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<typename T, typename Catagory, bool enabled=true>
class ITaskWareUnit : public ITaskWare
{
    $AsTaskUnit(ITaskWareUnit)
    Q_DISABLE_COPY_MOVE(ITaskWareUnit)
protected:
    ITaskWareUnit() = default;
    virtual ~ITaskWareUnit() = default;

protected:
    virtual QString $name() const final;
    virtual const QString& $catagory() const final;

public:
    static const QString CLASS_NAME;
};

template<typename T, typename Catagory, bool enabled>
QString ITaskWareUnit<T, Catagory, enabled>::$name() const
{
    return ITaskWareUnit::CLASS_NAME;
}

template<typename T, typename Catagory, bool enabled>
const QString& ITaskWareUnit<T, Catagory, enabled>::$catagory() const
{
    return Catagory::CLASS_NAME;
}

template<typename T, typename Catagory, bool enabled>
const QString ITaskWareUnit<T, Catagory, enabled>::CLASS_NAME = IMetaUtil::getBareTypeName<T>();

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
