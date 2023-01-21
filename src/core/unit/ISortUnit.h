#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ISortUnitHelper{
    template<typename T>
    QList<QPair<QString, QStringList>> getMaps(const QList<T*>&);

    template<typename T>
    QList<T*> toSortList(const QList<T*>&, const QStringList&);

    QStringList sort(const QList<QPair<QString, QStringList>>&);
};

struct ISortUnit
{
public:
    virtual QStringList orders() const;

private:
    template<typename T>
    static QVector<T*> sort(const QList<T*>&);
};

template<typename T>
QVector<T *> ISortUnit::sort(const QList<T *>& values)
{
    auto list = ISortUnitHelper::getMaps(values);
    auto strList = ISortUnitHelper::sort(list);
    return ISortUnitHelper::toSortList(values, strList);
}

template<typename T>
QList<QPair<QString, QStringList> > ISortUnitHelper::getMaps(const QList<T *>& values)
{
    QList<QPair<QString, QStringList>> sortPairs;
    for(const T* val : values){
        sortPairs.append({val->name(), val->orders()});
    }

    return sortPairs;
}


template<typename T>
QList<T *> ISortUnitHelper::toSortList(const QList<T *> &list, const QStringList &orders)
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

$PackageWebCoreEnd
