#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/detail/IHttpControllerAction.h"

$PackageWebCoreBegin


struct IHttpControllerInfo
{
public:
    void* handler{};
    QString className;
    QMap<QString, QString> classInfo;
    QVector<QMetaMethod> classMethods;

public:
    QVector<IHttpControllerAction> m_urlNodes;
};

$PackageWebCoreEnd
