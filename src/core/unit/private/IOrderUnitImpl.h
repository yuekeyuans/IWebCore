#pragma once

#include "base/IHeaderUtil.h"
//#include "core/unit/IOrderUnit.h"

$PackageWebCoreBegin

class IOrderUnit;
class IOrderUnitImpl
{
    $UseInstance(IOrderUnitImpl)
    Q_DISABLE_COPY_MOVE(IOrderUnitImpl)
private:
    IOrderUnitImpl();

    template<typename T>
    QList<T*> sort(const QList<T*>&);

    template<typename T>
    QList<IOrderUnit*> toOrderUnitList(const QList<T*>& );

};

template<typename T>
QList<T *> IOrderUnitImpl::sort(const QList<T *> & orders)
{
    auto units = toOrderUnitList(orders);

}

template<typename T>
QList<IOrderUnit*> IOrderUnitImpl::toOrderUnitList(const QList<T*>& orders)
{
    QList<IOrderUnit*> units;
    for(auto& order : orders){
        units.append(static_cast<IOrderUnit*>(order));
    }
    return units;
}

$PackageWebCoreEnd
