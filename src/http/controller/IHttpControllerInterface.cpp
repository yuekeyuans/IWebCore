#include "IHttpControllerInterface.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/IHttpManage.h"
#include "http/controller/IControllerAbort.h"
#include "http/controller/private/IHttpControllerInfo.h"

$PackageWebCoreBegin

void IControllerInterfaceHelper::registerController(void *handler, const QString &className,
                                                   const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods)
{
    auto info = ISpawnUtil::construct<IHttpControllerInfo>(handler, className, classInfo, methods);
    IHttpManage::instance()->registerUrlActionNodes(info.m_urlNodes);
}

$PackageWebCoreEnd
