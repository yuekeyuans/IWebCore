#include "IStatusControllerInterface.h"

#include "web/IWebAssert.h"
#include "web/controller/private/IStatusControllerInterfaceImpl.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

void IStatusControllerInterfaceProxy::registerController(const IControllerInfo& info)
{
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

void IStatusControllerInterfaceProxy::unRegisterController(const IControllerInfo& info)
{
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
