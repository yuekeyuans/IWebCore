#include "IControllerInterface.h"
#include "web/IWebAssert.h"
#include "web/controller/private/IControllerInterfaceImpl.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

void IControllerInterfaceProxy::registerController(const IControllerInfo& info)
{
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

void IControllerInterfaceProxy::unRegisterController(const IControllerInfo& info)
{
    IControllerInterfaceImpl::checkUrlMappings(info);

    auto functionNodes = IControllerInterfaceImpl::createMappingLeaves(info);
    if(!functionNodes.empty()){
        IControllerManage::unRegisterUrlActionNodes(functionNodes);
    }
}

void IControllerInterfaceProxy::unRegisterError()
{
    $Ast->fatal("unregister_controller_do_not_use_singleton");
}



$PackageWebCoreEnd
