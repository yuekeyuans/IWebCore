#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class IRegisterInstanceUnit
{
    Q_DISABLE_COPY_MOVE(IRegisterInstanceUnit)
protected:
    IRegisterInstanceUnit() = default;
    virtual ~IRegisterInstanceUnit() = default;

public:
    virtual void registerToBase() = 0;

private:
    class IRegisterInstanceUnitPrivate{
    public:
        IRegisterInstanceUnitPrivate();
    };

    static IRegisterInstanceUnitPrivate m_IRegisterInstanceUnitPrivate;
    virtual void* IRegisterInstanceUnitTouch(){
        return &m_IRegisterInstanceUnitPrivate;
    }
};

template<class T, bool enabled>
typename IRegisterInstanceUnit<T, enabled>::IRegisterInstanceUnitPrivate
IRegisterInstanceUnit<T, enabled>::m_IRegisterInstanceUnitPrivate;

template<class T, bool enabled>
IRegisterInstanceUnit<T, enabled>::IRegisterInstanceUnitPrivate::IRegisterInstanceUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            auto inst = T::instance();
            inst->registerToBase();
        });
    }
}

$PackageWebCoreEnd
