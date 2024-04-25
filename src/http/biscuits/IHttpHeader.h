#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpHeader
{
    inline static const QString Location = "Location";
    inline static const QString ContentLength = "Content-Length";
    inline static const QString ContentType = "Content-Type";
    inline static const QString ContentDisposition = "Content-Disposition";
    inline static const QString ContentTransferEncoding = "Content-Transfer-Encoding";
    inline static const QString Cookie = "Cookie";
    inline static const QString SetCookie = "Set-Cookie";
};

$PackageWebCoreEnd
