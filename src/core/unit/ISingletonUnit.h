#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"

$PackageWebCoreBegin

template<typename T>
class ISingletonUnit
{
protected:
    ISingletonUnit();
    virtual ~ISingletonUnit() = default;

    ISingletonUnit(const ISingletonUnit&) = delete;
    ISingletonUnit& operator=(const ISingletonUnit&) = delete;

public:
    static T* instance();
};

namespace ISingletonUnitDetail
{
    template<typename T, typename = decltype(T::instance())>
    T* getInstance(void*);

    template<typename T>
    T* getInstance(...);

    void abortError(QString);
}

template<typename T>
T* ISingletonUnit<T>::instance()
{
    static T instance{};
    return &instance;
}

template<typename T>
ISingletonUnit<T>::ISingletonUnit()
{
    static std::atomic_bool flag{false};
    if(flag){
        ISingletonUnitDetail::abortError("class name:" + IMetaUtil::getTypename<T>());
    }
    flag = true;
}

template<typename T, typename U>
T* ISingletonUnitDetail::getInstance(void*)
{
    return T::instance();
}

template<typename T>
T* ISingletonUnitDetail::getInstance(...)
{
    static T t;
    return &t;
}

$PackageWebCoreEnd
