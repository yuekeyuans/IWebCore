#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/detail/IHttpRouteLeafNode.h"

$PackageWebCoreBegin


struct IHttpControllerInfo
{
public:
    void* handler{};
    QString className;
    QMap<QString, QString> classInfo;
    QVector<QMetaMethod> classMethods;

public:
    QVector<IHttpRouteLeafNode> m_urlNodes;
};

$PackageWebCoreEnd
