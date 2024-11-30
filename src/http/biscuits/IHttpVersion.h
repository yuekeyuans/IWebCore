#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

enum class IHttpVersion
{
    VERSION_1_0 = 0,    // note: v0.9 is not supported
    VERSION_1_1,
    VERSION_2_0,

    UNKNOWN,
};

namespace IHttpVersionUtil {
    const IString& toString(IHttpVersion version);
    IHttpVersion toVersion(const QString& version);
    IHttpVersion toVersion(const IString& version);
}

$PackageWebCoreEnd
