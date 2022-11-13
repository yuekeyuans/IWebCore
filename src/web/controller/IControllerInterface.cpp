#include "IControllerInterface.h"
#include "web/IWebAssert.h"
#include "web/controller/private/IControllerInfo.h"
#include "web/controller/private/IControllerInterfaceImpl.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

void IControllerInterfaceProxy::registerController(void *handler, const QString &className,
                                                   const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    IControllerInfo info;
    info.handler = handler;
    info.className = className;
    info.classInfo = classInfo;
    info.classMethods = methods;

    IControllerInterfaceImpl::checkUrlMappings(info);
    auto functionNodes = IControllerInterfaceImpl::createMappingLeaves(info);
    if(!functionNodes.empty()){
        IControllerManage::registerUrlActionNodes(functionNodes);
    }
}

void IControllerInterfaceProxy::registerError()
{
    $Ast->fatal("register_controller_do_not_use_singleton");
}

void IControllerInterfaceProxy::unRegisterError()
{
    $Ast->fatal("unregister_controller_do_not_use_singleton");
}

void IControllerInterfaceProxy::unRegisterController(void *handler, const QString &className,
                                                     const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    IControllerInfo info;
    info.handler = handler;
    info.className = className;
    info.classInfo = classInfo;
    info.classMethods = methods;

    IControllerInterfaceImpl::checkUrlMappings(info);
    auto functionNodes = IControllerInterfaceImpl::createMappingLeaves(info);
    if(!functionNodes.empty()){
        IControllerManage::unRegisterUrlActionNodes(functionNodes);
    }
}

$PackageWebCoreEnd
