#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

struct IControllerInfo
{
    void* handler;
    QString className;

    QMap<QString, QString> clsInfo;
    QVector<QMetaMethod> methods;

};

$PackageWebCoreEnd
