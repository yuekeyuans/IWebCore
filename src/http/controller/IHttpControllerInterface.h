#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"
#include "http/IHttpTaskCatagory.h"
#include "core/util/ISpawnUtil.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IHttpControllerInterface : public ITaskWareUnit<T, IHttpTaskCatagory, enabled>, public ISingletonUnit<T>
{
public:
    virtual void $task() final;
};

template<typename T, bool enabled>
void IHttpControllerInterface<T, enabled>::$task()
{
    if constexpr (enabled){
        auto className = IMetaUtil::getMetaClassName (T::staticMetaObject);
        auto classInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
        auto classMethods = IMetaUtil::getMetaMethods(T::staticMetaObject);
        ISpawnUtil::construct<void, void*, const QString&, const QMap<QString, QString> &, const QVector<QMetaMethod>&>
            (this, className, classInfo, classMethods);
    }
}

$PackageWebCoreEnd
