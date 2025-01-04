#include "IHttpControllerInterface.h"
#include "http/controller/detail/IHttpControllerInterfaceDetail.h"
#include "http/mappings/IHttpControllerMapping.h"

$PackageWebCoreBegin

void detail::registerController(void *handler,
                                const QString &className,
                                const QMap<QString, QString> &classInfo,
                                const QVector<QMetaMethod> &methods)
{
    IHttpControllerInfo info(handler, className, classInfo, methods);
    for(const IHttpControllerAction& action : info.m_urlNodes){
        IHttpControllerMapping::instance()->registerUrlActionNode(action);
    }
}

$PackageWebCoreEnd
