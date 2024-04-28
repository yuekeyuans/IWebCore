#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IRegisterGadgetUnit
{
    $AsTaskUnit(IRegisterGadgetUnit)
public:
    IRegisterGadgetUnit() = default;

protected:
    virtual void registerToBase(void* handler, const QMap<QString, QString>& clsInfo,
                                const QVector<QMetaMethod>& methods) = 0;
};

$UseTaskUnit(IRegisterGadgetUnit)
{
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

$PackageWebCoreEnd
