#include "IHttpControllerInterface.h"
#include "http/controller/IHttpManage.h"
#include "http/controller/IControllerAbort.h"
#include "http/controller/private/IHttpControllerInfo.h"
//#include "http/controller/private/IControllerInterfaceHelper.h"

$PackageWebCoreBegin

void IControllerInterfaceHelper::registerController(void *handler, const QString &className,
                                                   const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    auto info = IHttpControllerInfoHelper::construct(handler, className, classInfo, methods);

//    IControllerInterfaceHelper::checkUrlMappings(info);
//    auto functionNodes = info.createMappingLeaves(info);
//    if(!functionNodes.empty()){
//        IHttpManage::instance()->registerUrlActionNodes(functionNodes);
//    }
}

$PackageWebCoreEnd
