#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpHeader
{
    static const QString Location;
    static const QString ContentLength;
    static const QString ContentType;
    static const QString ContentDisposition;
    static const QString ContentTransferEncoding;
    static const QString Cookie;
    static const QString SetCookie;
};

$PackageWebCoreEnd
