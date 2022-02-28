#pragma once

#include "base/IHeaderUtil.h"
#include "assertion/IAssertManage.h"
#include "common/support/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true, const char* type = FatalType>
class IAssertInterface : private IRegisterInstanceUnit<T, enabled>
{
public:
    IAssertInterface() = default;
    virtual QString getKey() = 0;
    virtual QString getReason() = 0;
    virtual QString getDescription() = 0;
    virtual QString getSolution() = 0;

public:
    virtual void registerToBase() override {
        IAssertInfo info;
        info.key = getKey();
        info.reason = getReason();
        info.description = getDescription();
        info.solution = getSolution();

        if(type == FatalType){  // 这样写可以的, 直接比较地址
            IAssertManage::registerFatalInfo(info);
        }else{
            IAssertManage::registerWarnInfo(info);
        }
    };
};


template<typename T, bool enabled = true>
using IFatalAssertInterface = IAssertInterface<T, enabled, FatalType>;

template<typename T, bool enabled = true>
using IWarningAssertInterface = IAssertInterface<T, enabled, WarningType>;

$PackageWebCoreEnd
