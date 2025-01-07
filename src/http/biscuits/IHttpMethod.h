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
    IStringView toString(IHttpMethod);
    IHttpMethod toMethod(const QString&);
    IHttpMethod toMethod(const IString&);
    const IStringList & methodNames();
}

$PackageWebCoreEnd
