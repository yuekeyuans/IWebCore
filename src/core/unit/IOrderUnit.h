#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IOrderUnitHelper{
    template<typename T>
    QList<T*> sort(const QList<T*>&);
    QStringList sort(const QMap<QString, QStringList>&);
};

struct IOrderUnit
{
public:
    virtual QStringList orders() const;

private:
    template<typename T>
    static QList<T*> sort(const QList<T*>&);
};

template<typename T>
QList<T *> IOrderUnit::sort(const QList<T *>& values)
{
    return IOrderUnitHelper::sort(values);
}

template<typename T>
static QList<QPair<QString, QStringList>> toSortMap(const QList<T *>& values)
{
    QList<QPair<QString, QStringList>> sortPairs;
    for(const T* val : values){
        sortPairs.append({val->name(), val->orders()});
    }

    return sortPairs;
}


template<typename T>
static QList<T *> toSortList(const QList<T *> &list, const QStringList &orders)
{
    QList<T*> ret;

    for(const auto& order : orders){
        for(auto val : list){
            if(val->name() == order){
                ret.append(val);
            }
        }
    }

    return ret;
}

template<typename T>
QList<T*> IOrderUnitHelper::sort(const QList<T*>& values)
{
    auto map = toSortMap(values);
    auto result = IOrderUnitHelper::sort(map);
    return toSortList(values, result);
}

$PackageWebCoreEnd
