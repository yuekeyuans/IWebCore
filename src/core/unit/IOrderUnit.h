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

    static QList<IOrderUnit *> sortUnit(QList<IOrderUnit *> values);
};

template<typename T>
void IOrderUnit::sortUnit(QList<T*>& values){
    QList<IOrderUnit*> temp;
    for(auto val : values){
        temp.append(static_cast<IOrderUnit*>(val));
    }

    temp = sortUnit(temp);
    values.clear();
    for(auto val : temp){
        values.append(dynamic_cast<T*>(val));
    }
}


$PackageWebCoreEnd
