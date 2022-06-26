#include "IControllerInterface.h"
#include "web/IWebAssert.h"
#include "web/controller/private/IControllerInterfaceImpl.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

void IControllerInterfaceProxy::registerController(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaMethod> &methods)
{
    IControllerInterfaceImpl::checkUrlMappings(handler, clsInfo, methods);

    auto functionNodes = IControllerInterfaceImpl::createMappingLeaves(handler, clsInfo, methods);
    if(!functionNodes.empty()){
        IControllerManage::registerUrlFunctions(functionNodes);
    }
}

void IControllerInterfaceProxy::registerError()
{
    $Ast->fatal("register_controller_do_not_use_singleton");
}

void IControllerInterfaceProxy::unRegisterController(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaMethod> &methods)
{
    IControllerInterfaceImpl::checkUrlMappings(handler, clsInfo, methods);

    auto functionNodes = IControllerInterfaceImpl::createMappingLeaves(handler, clsInfo, methods);
    if(!functionNodes.empty()){
        IControllerManage::unRegisterUrlFunctions(functionNodes);
    }
}

void IControllerInterfaceProxy::unRegisterError()
{
    $Ast->fatal("unregister_controller_do_not_use_singleton");
}

$PackageWebCoreEnd
