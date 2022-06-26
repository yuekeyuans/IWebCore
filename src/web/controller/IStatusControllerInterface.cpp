#include "IStatusControllerInterface.h"

#include "web/IWebAssert.h"
#include "web/controller/private/IStatusControllerInterfaceImpl.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

void IStatusControllerInterfaceProxy::registerController(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaMethod> &methods)
{
    auto nodes = IStatusControllerInterfaceImpl::generateStatusFunctionNodes(handler, clsInfo, methods);

    if(nodes.isEmpty()){
        IStatusControllerInterfaceImpl::checkStatusNodes(nodes);
        IControllerManage::registerStatusFunctions(nodes);
    }
}

void IStatusControllerInterfaceProxy::registerError()
{
    $Ast->fatal("register_controller_do_not_use_singleton");
}

void IStatusControllerInterfaceProxy::unRegisterController(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaMethod> &methods)
{
    auto nodes = IStatusControllerInterfaceImpl::generateStatusFunctionNodes(handler, clsInfo, methods);

    if(nodes.isEmpty()){
        IStatusControllerInterfaceImpl::checkStatusNodes(nodes);
        IControllerManage::unRegisterStatusFunctions(nodes);
    }
}

void IStatusControllerInterfaceProxy::unRegisterError()
{
    $Ast->fatal("unregister_controller_do_not_use_singleton");
}



$PackageWebCoreEnd
