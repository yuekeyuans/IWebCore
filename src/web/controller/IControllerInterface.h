#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "web/controller/IControllerManage.h"
#include "web/node/IUrlFunctionNode.h"
#include "core/task/IControllerTaskUnit.h"

$PackageWebCoreBegin

namespace IControllerInterfaceImplProxy{
    void checkUrlMappings(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);
    QVector<IUrlFunctionNode> createMappingLeaves(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);
    void checkStatusCodes(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaMethod> &methods);

    void registerError();

};

template<typename T, bool enabled = true>
class IControllerInterface : public IControllerTaskUnit<T, enabled>
{
public:
    IControllerInterface() = default;
    virtual ~IControllerInterface() = default;
    virtual void task() final;

    void registerController();
    void unRegisterController();
};

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::task()
{
    registerController();
}

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::registerController()
{
    if(this != T::instance()){
        IControllerInterfaceImplProxy::registerError();
    }

    auto clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    IControllerInterfaceImplProxy::checkUrlMappings(this, clsInfo, methods);

    auto functionNodes = IControllerInterfaceImplProxy::createMappingLeaves(this, clsInfo, methods);
    if(!functionNodes.empty()){
        IControllerManage::registerUrlFunctions(functionNodes);
    }
}

template<typename T, bool enabled>
void IControllerInterface<T, enabled>::unRegisterController()
{
    auto inst = T::instance();
    auto clsInfo = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
//    registerControllerFun(inst, clsInfo, methods);
}

$PackageWebCoreEnd
