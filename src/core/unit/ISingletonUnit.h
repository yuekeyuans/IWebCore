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

// TODO: GlobalAstError

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

$PackageWebCoreEnd
