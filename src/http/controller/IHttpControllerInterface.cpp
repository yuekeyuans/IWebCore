#include "IHttpControllerInterface.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/IHttpManage.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/controller/detail/IHttpControllerInfo.h"
#include "http/controller/mapping/IHttpRouteMapping.h"

$PackageWebCoreBegin

void detail::registerController(void *handler, const QString &className,
                                                   const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    auto info = ISpawnUtil::construct<IHttpControllerInfo>(handler, className, classInfo, methods);
    IHttpRouteMapping::instance()->registerUrlActionNodes(info.m_urlNodes);
}

$PackageWebCoreEnd
