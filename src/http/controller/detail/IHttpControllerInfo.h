#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/detail/IHttpRouteLeaf.h"

$PackageWebCoreBegin


struct IHttpControllerInfo
{
public:
    void* handler{};
    QString className;
    QMap<QString, QString> classInfo;
    QVector<QMetaMethod> classMethods;

public:
    QVector<IHttpRouteLeaf> m_urlNodes;
};

$PackageWebCoreEnd
