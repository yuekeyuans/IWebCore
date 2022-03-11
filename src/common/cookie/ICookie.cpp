#include "ICookie.h"
#include "common/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

QStringList ICookie::keys()
{
    return raw->m_cookieParameters.keys();
}

QStringList ICookie::values()
{
    return raw->m_cookieParameters.values();
}

void ICookie::setCookie(const QString &key, const QString &value)
{
    raw->m_responseCookies[key] = value;
}

$PackageWebCoreEnd
