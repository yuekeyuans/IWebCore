#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IRegisterTypeUnit
{
public:
    IRegisterTypeUnit() = default;
    virtual ~IRegisterTypeUnit() = default;

private:
    class IRegisterTypeUnitPrivate{
    public:
        IRegisterTypeUnitPrivate(){
            if(enabled){
                static std::once_flag flag;
                std::call_once(flag, [](){
                    T::web_core_init_registerType();
                });
            }
        }
    };

    static IRegisterTypeUnitPrivate m_IRegisterTypeUnitPrivate;
    virtual void* IRegisterTypeUnitPrivateTouch(){
        return &m_IRegisterTypeUnitPrivate;
    }
};

template<typename T, bool enabled>
typename IRegisterTypeUnit<T, enabled>::IRegisterTypeUnitPrivate
IRegisterTypeUnit<T, enabled>::m_IRegisterTypeUnitPrivate;

$PackageWebCoreEnd
