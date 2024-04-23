#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

enum class IHttpVersion
{
    VERSION_1_0 = 0,    // note: v0.9 is not supported
    VERSION_1_1,
    VERSION_2_0,

    UNKNOWN,
};

namespace IHttpVersionUtil {
    QString toString(IHttpVersion version);
    IHttpVersion toVersion(const QString& version);
    const QStringList& getVersionStrings();
}

$PackageWebCoreEnd
