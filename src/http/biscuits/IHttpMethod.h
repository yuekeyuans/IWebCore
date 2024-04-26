#pragma once
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

enum class IHttpMethod {
    GET = 0,
    POST,
    PUT,
    DELETED,
    PATCH,
    HEAD,
    OPTIONS,
    UNKNOWN
};

namespace IHttpMethodUtil{
    QString toString(IHttpMethod);
    IHttpMethod toMethod(const QString&);
    const QStringList& methodNames();
}

$PackageWebCoreEnd
