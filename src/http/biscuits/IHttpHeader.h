#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpHeader
{
    inline static constexpr char Location[] = "Location";
    inline static constexpr char ContentLength[] = "Content-Length";
    inline static constexpr char ContentType[] = "Content-Type";
    inline static constexpr char ContentDisposition[] = "Content-Disposition";
    inline static constexpr char ContentTransferEncoding[] = "Content-Transfer-Encoding";
    inline static constexpr char Cookie[] = "Cookie";
    inline static constexpr char SetCookie[] = "Set-Cookie";
};

$PackageWebCoreEnd
