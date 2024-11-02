#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/detail/IHttpAction.h"

$PackageWebCoreBegin


struct IHttpControllerInfo
{
public:
    void* handler{};
    QString className;
    QMap<QString, QString> classInfo;
    QVector<QMetaMethod> classMethods;

public:
    QVector<IHttpAction> m_urlNodes;
};

$PackageWebCoreEnd
