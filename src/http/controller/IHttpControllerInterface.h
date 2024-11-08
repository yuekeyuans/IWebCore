#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"
#include "http/IHttpTaskCatagory.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IHttpControllerInterface : public ITaskWareUnit<T, IHttpTaskCatagory, enabled>, public ISingletonUnit<T>
{
public:
    virtual void $task() final;
};

namespace detail
{
    void registerController(void* handler, const QString& className,
                            const QMap<QString, QString>& classMap,
                            const QVector<QMetaMethod>& methods);
}

template<typename T, bool enabled>
void IHttpControllerInterface<T, enabled>::$task()
{
    if constexpr (enabled){
        auto className = IMetaUtil::getMetaClassName (T::staticMetaObject);
        auto classInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
        auto classMethods = IMetaUtil::getMetaMethods(T::staticMetaObject);
        detail::registerController(this, className, classInfo, classMethods);
    }
}

$PackageWebCoreEnd
