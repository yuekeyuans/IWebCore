#include "IHttpVersion.h"

$PackageWebCoreBegin

QString IHttpVersionHelper::toString(IHttpVersion version)
{
    const auto& versions = getVersionStrings();
    return versions[static_cast<int>(version)];
}

IHttpVersion IHttpVersionHelper::toVersion(const QString& version)
{
    const auto& versions = getVersionStrings();
    if(versions.contains(version)){
        return IHttpVersion(versions.indexOf(version.toUpper()));
    }
    return IHttpVersion::UNKNOWN;
}

const QStringList &IHttpVersionHelper::getVersionStrings()
{
    static QStringList m_versionStrings = {
        "HTTP/1.0",
        "HTTP/1.1",
        "HTTP/2.0",
        "UNKNOWN"
    };

    return m_versionStrings;
}

$PackageWebCoreEnd
