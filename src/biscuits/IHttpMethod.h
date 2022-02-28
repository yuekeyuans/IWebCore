#pragma once
#include "base/IHeaderUtil.h"

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

namespace IHttpMethodHelper{
    QString toString(IHttpMethod);
    IHttpMethod toMethod(const QString&);
    inline const QStringList& methodNames();
};

$PackageWebCoreEnd
