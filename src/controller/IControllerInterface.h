#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "common/task/IControllerTaskUnit.h"
#include "common/node/IUrlFunctionNode.h"

$PackageWebCoreBegin

namespace IControllerInterfaceImplProxy{
    void checkUrlMappings(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);
    QVector<IUrlFunctionNode> createMappingLeaves(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);
    void checkStatusCodes(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaMethod> &methods);
};

template<typename T, bool enabled = true>
class IControllerInterface : public IControllerTaskUnit<T, enabled>
{
public:
    IControllerInterface() = default;
    virtual ~IControllerInterface() = default;
    virtual void task() final;

protected:
    virtual void registerControllerFun(void *handler, const QMap<QString, QString> &clsInfo,
                                const QVector<QMetaMethod> &methods) = 0;
};

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::task(){
    auto inst = T::instance();
    auto clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    registerControllerFun(inst, clsInfo, methods);
}

$PackageWebCoreEnd
