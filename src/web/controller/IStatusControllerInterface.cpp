#include "IStatusControllerInterface.h"

#include "web/IWebAssert.h"
#include "web/controller/private/IStatusControllerInterfaceImpl.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

void IStatusControllerInterfaceProxy::registerController(void *handler, const QString &className,
                                                         const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    IControllerInfo info;
    info.handler = handler;
    info.className = className;
    info.classInfo = classInfo;
    info.classMethods = methods;

    auto nodes = IStatusControllerInterfaceImpl::generateStatusFunctionNodes(info);

    if(nodes.isEmpty()){
        IStatusControllerInterfaceImpl::checkStatusNodes(nodes);
        IControllerManage::registerStatusActionNodes(nodes);
    }
}

void IStatusControllerInterfaceProxy::registerError()
{
    $Ast->fatal("register_controller_do_not_use_singleton");
}

void IStatusControllerInterfaceProxy::unRegisterController(void *handler, const QString &className,
                                                           const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    IControllerInfo info;
    info.handler = handler;
    info.className = className;
    info.classInfo = classInfo;
    info.classMethods = methods;

    auto nodes = IStatusControllerInterfaceImpl::generateStatusFunctionNodes(info);

    if(nodes.isEmpty()){
        IStatusControllerInterfaceImpl::checkStatusNodes(nodes);
        IControllerManage::unRegisterStatusActionNodes(nodes);
    }
}

void IStatusControllerInterfaceProxy::unRegisterError()
{
    $Ast->fatal("unregister_controller_do_not_use_singleton");
}

$PackageWebCoreEnd
