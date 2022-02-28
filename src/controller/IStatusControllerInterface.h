#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "common/task/IControllerTaskUnit.h"

#include "configuration/IConfigurationManage.h"
#include "common/node/IStatusFunctionNode.h"

#include "controller/private/IStatusControllerInterfaceImpl.h"
#include "controller/IControllerManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IStatusControllerInterface : public IControllerTaskUnit<T, enabled>
{
protected:
    IStatusControllerInterface() = default;
    virtual ~IStatusControllerInterface() = default;

public:
    virtual void task() final;
    virtual void registerControllerFun(void* handler, const QMap<QString, QString>& clsInfo,
                                const QVector<QMetaMethod>& methods) = 0;
};

template<typename T, bool enabled>
void IStatusControllerInterface<T, enabled>::task(){
    auto inst = T::instance();
    auto clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    registerControllerFun(inst, clsInfo, methods);
}

$PackageWebCoreEnd
