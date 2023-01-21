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
    enum SortFlag{
        First,
        Last,
        Before,
        After,
        Higher,
        Lower
    };

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
    return {};
}


template<typename T>
QList<T *> ISortUnitHelper::toSortList(const QList<T *> &, const QStringList &)
{
    return {};
}

$PackageWebCoreEnd
