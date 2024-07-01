#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IGadgetInfo.h"

$PackageWebCoreBegin

struct IHttpControllerInfo : public IGadgetInfo
{
};

namespace IHttpControllerInfoHelper{

IHttpControllerInfo construct(void *handler, const QString &className,
                              const QMap<QString, QString> &classInfo, const QVector<QMetaMethod> &methods);
}

$PackageWebCoreEnd
