#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConstantUtil.h"

$PackageWebCoreBegin

struct IOrderUnit
{
public:
    virtual QString name() const = 0;
    virtual double order() const;

public:
    template<typename T>
    static void sortUnit(QList<T*>& values);
};

inline double IOrderUnit::order() const
{
    return 50;
}

template<typename T>
void IOrderUnit::sortUnit(QList<T*>& values){
    std::sort(values.begin(), values.end(), [](T* lhs, T* rhs) -> bool{
        if(lhs->order() != rhs->order()){
            return lhs->order() < rhs->order();
        }

        return lhs->name() < rhs->name();
    });
}

$PackageWebCoreEnd
