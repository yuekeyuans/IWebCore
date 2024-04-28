#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/assert/IGlobalAssert.h"

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
    static T* instance() {
        static T instance;
        return &instance;
    }
};

namespace ISingletonUnitHelper
{
    template<typename T>
    T* getInstance(int);

    template<typename T>
    T* getInstance(...);
}

template<typename T>
ISingletonUnit<T>::ISingletonUnit()
{
    static std::atomic_bool flag{false};
    if(flag){
        IAssertInfo info;
        info.className = IMetaUtil::getTypename<T>();
        IGlobalAssert::instance()->fatal("SingletonInstanceCreateError", info);
    }
    flag = true;
}

template<typename T>
T* ISingletonUnitHelper::getInstance(int){
    return T::instance();
}

template<typename T>
T* ISingletonUnitHelper::getInstance(...)
{
    static T t;
    return &t;
}


$PackageWebCoreEnd
