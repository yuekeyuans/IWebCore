#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"

$PackageWebCoreBegin

/*!
 * used for registration instace to base
 */
template<typename T, bool enabled = true>
class IRegisterGadgetUnit{
public:
    IRegisterGadgetUnit() = default;

protected:
    virtual void registerToBase(void* handler, const QMap<QString, QString>& clsInfo,
                                const QVector<QMetaMethod>& methods) = 0;

private:
    class IRegisterGadgetUnitPrivate{
    public:
        IRegisterGadgetUnitPrivate();
    };

//    friend class IRegisterGadgetUnitPrivate;
    static IRegisterGadgetUnitPrivate m_IRegisterGadgetUnitPrivate;

    virtual void* IRegisterUnitPrivateTouch(){
        return &m_IRegisterGadgetUnitPrivate;
    }
};


template<typename T, bool enabled>
IRegisterGadgetUnit<T, enabled>::IRegisterGadgetUnitPrivate::IRegisterGadgetUnitPrivate(){
    if(enabled){
        static std::once_flag flag;
        std::call_once(flag, [](){
            static T t;
            auto clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
            auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
            t.registerToBase(&t , clsInfo, methods);
        });
    }
}

template<typename T, bool enabled>
typename IRegisterGadgetUnit<T, enabled>::IRegisterGadgetUnitPrivate
        IRegisterGadgetUnit<T, enabled>::m_IRegisterGadgetUnitPrivate;

$PackageWebCoreEnd
