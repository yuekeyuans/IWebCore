#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"

$PackageWebCoreBegin

// dead code
struct IGadgetInfo
{
    void* handler{};
    QString className;
    QMap<QString, QString> classInfo;
    QVector<QMetaMethod> classMethods;
};

template<typename T>
IGadgetInfo construct(T* obj)
{
    IGadgetInfo info;
    info.ptr = obj;
    info.className = IMetaUtil::getTypename<T>();
    info.classInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    info.classMethods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    return info;
}

$PackageWebCoreEnd
