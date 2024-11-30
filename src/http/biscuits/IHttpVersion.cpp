#include "IHttpVersion.h"

$PackageWebCoreBegin

namespace detail
{
    const IStringList& getVersionStrings()
    {
        static const IStringList m_versionStrings = {
            "HTTP/1.0",
            "HTTP/1.1",
            "HTTP/2.0",
            "UNKNOWN"
        };
        return m_versionStrings;
    }
}

const IString& IHttpVersionUtil::toString(IHttpVersion version)
{
    static const auto& versions = detail::getVersionStrings();
    if(static_cast<int>(version) < 0 || static_cast<int>(version) >3){
        return versions.last();
    }
    return versions[static_cast<int>(version)];
}

IHttpVersion IHttpVersionUtil::toVersion(const QString& version)
{
    return toVersion((IString(version.toUtf8())));
}

IHttpVersion IHttpVersionUtil::toVersion(const IString& version)
{
    static const auto& versions = detail::getVersionStrings();
    auto index = versions.indexOf(version);
    if(index < 0){
        return IHttpVersion::UNKNOWN;
    }
    return IHttpVersion(index);
}

$PackageWebCoreEnd
