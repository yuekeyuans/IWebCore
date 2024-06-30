#include "IHttpControllerInterface.h"
#include "http/controller/IHttpManage.h"
#include "http/controller/IControllerAbort.h"
#include "http/controller/private/IHttpControllerInfo.h"
#include "http/controller/private/IControllerInterfaceHelper.h"

$PackageWebCoreBegin

void IControllerInterfaceHelper::registerController(void *handler, const QString &className,
                                                   const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    IHttpControllerInfo info;
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
    IControllerAbort::abortregister_controller_do_not_use_singleton($ISourceLocation);
}

$PackageWebCoreEnd
