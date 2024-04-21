#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpControllerInfo
{
    void* handler{};
    QString className;
    QMap<QString, QString> classInfo;
    QVector<QMetaMethod> classMethods;
};

$PackageWebCoreEnd
