#include "IControllerInterface.h"
#include "web/IWebAssert.h"
#include "web/controller/IControllerManage.h"
#include "web/controller/private/IControllerInfo.h"
#include "web/controller/private/IControllerInterfaceHelper.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

void IControllerInterfaceHelper::registerController(void *handler, const QString &className,
                                                   const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    IControllerInfo info;
    info.handler = handler;
    info.className = className;
    info.classInfo = classInfo;
    info.classMethods = methods;

    IControllerInterfaceHelper::checkUrlMappings(info);
    auto functionNodes = IControllerInterfaceHelper::createMappingLeaves(info);
    if(!functionNodes.empty()){
        IControllerManage::instance()->registerUrlActionNodes(functionNodes);
    }
}

void IControllerInterfaceHelper::registerError()
{
    $Ast->fatal("register_controller_do_not_use_singleton");
}

void IControllerInterfaceHelper::unRegisterError()
{
    $Ast->fatal("unregister_controller_do_not_use_singleton");
}

void IControllerInterfaceHelper::unRegisterController(void *handler, const QString &className,
                                                     const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    IControllerInfo info;
    info.handler = handler;
    info.className = className;
    info.classInfo = classInfo;
    info.classMethods = methods;

    IControllerInterfaceHelper::checkUrlMappings(info);
    auto functionNodes = IControllerInterfaceHelper::createMappingLeaves(info);
    if(!functionNodes.empty()){
        IControllerManage::instance()->unRegisterUrlActionNodes(functionNodes);
    }
}

$PackageWebCoreEnd
