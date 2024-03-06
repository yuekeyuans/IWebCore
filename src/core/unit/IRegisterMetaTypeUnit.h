#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IRegisterMetaTypeUnit
{
public:
    IRegisterMetaTypeUnit() = default;
    virtual ~IRegisterMetaTypeUnit() = default;

private:
    class IRegisterMetaTypeetUnitPrivate{
    public:
        IRegisterMetaTypeetUnitPrivate(){
            if(enabled){
                static std::once_flag initRegisterFlag;
                std::call_once(initRegisterFlag, [](){
                    IMetaUtil::registerMetaType<T>();
                });
            }
        }
    };

    static IRegisterMetaTypeetUnitPrivate m_IRegisterMetaTypeetUnitPrivate;
    virtual void* IRegisterMetaTypeetUnitPrivateTouch(){
        return &m_IRegisterMetaTypeetUnitPrivate;
    }
};

template <typename T, bool enabled>
typename IRegisterMetaTypeUnit<T, enabled>::IRegisterMetaTypeetUnitPrivate
IRegisterMetaTypeUnit<T, enabled>::m_IRegisterMetaTypeetUnitPrivate;

$PackageWebCoreEnd
