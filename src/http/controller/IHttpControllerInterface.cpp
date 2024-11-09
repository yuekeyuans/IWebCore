#include "IHttpControllerInterface.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/detail/IHttpControllerAction.h"
#include "http/mappings/IHttpControllerMapping.h"

$PackageWebCoreBegin

void detail::registerController(void *handler,
                                const QString &className,
                                const QMap<QString, QString> &classInfo,
                                const QVector<QMetaMethod> &methods)
{
    auto actions = ISpawnUtil::construct<QVector<IHttpControllerAction>>(handler, className, classInfo, methods);
    for(const auto& action : actions){
        IHttpControllerMapping::instance()->registerUrlActionNode(action);
    }
}

$PackageWebCoreEnd
