#include "IControllerInterface.h"
#include "web/IWebAssert.h"
#include "web/controller/IHttpManage.h"
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
        IHttpManage::instance()->registerUrlActionNodes(functionNodes);
    }
}

void IControllerInterfaceHelper::registerError()
{
    $Ast->fatal("register_controller_do_not_use_singleton");
}

$PackageWebCoreEnd
