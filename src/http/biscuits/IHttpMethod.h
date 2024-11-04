#pragma once

#include "core/util/IHeaderUtil.h"

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
    IHttpMethod toMethod(std::string_view);
    const QStringList& methodNames();
}

$PackageWebCoreEnd
