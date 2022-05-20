#include "IControllerInterface.h"
#include "web/controller/private/IControllerInterfaceImpl.h"

$PackageWebCoreBegin

void IControllerInterfaceImplProxy::checkUrlMappings(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods){
    return  IControllerInterfaceImpl::checkUrlMappings(handler, clsInfo, methods);
}

void IControllerInterfaceImplProxy::checkStatusCodes(void *handler, const QMap<QString, QString> &clsInfo
                                                     , const QVector<QMetaMethod> &methods){
    return IControllerInterfaceImpl::checkStatusCodes(handler, clsInfo, methods);
}

QVector<IUrlFunctionNode> IControllerInterfaceImplProxy::createMappingLeaves(void *handler, const QMap<QString, QString> &clsInfo
                                                        , const QVector<QMetaMethod> &methods){
    return IControllerInterfaceImpl::createMappingLeaves(handler, clsInfo, methods);
}

$PackageWebCoreEnd
