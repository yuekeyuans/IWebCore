#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

/**
 * @brief The IOrderUnit struct
 * 对, 设计 又被改掉了, 现在改成直接使用数字作为 order 顺序，有一点是，数字是double 类型，可以通过这个来映射对象之间的相互关系
 */
struct IOrderUnit
{
public:
    virtual QString name() const = 0;
    virtual double order() const;

public:
    template<typename T>
    static void sortUnit(QList<T*>& values);
};

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
