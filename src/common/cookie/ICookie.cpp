#include "ICookie.h"
#include "common/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

QStringList ICookie::keys()
{
    const auto& cookies = raw->m_requestCookieParameters;
    QStringList keys;
    for(const auto& cookie : cookies){
        keys.append(cookie.first);
    }
    return keys;
}

QStringList ICookie::values()
{
    const auto& cookies = raw->m_requestCookieParameters;
    QStringList values;
    for(const auto& cookie : cookies){
        auto value = cookie.second;
        if(!value.isEmpty()){
            values.append(value);
        }

    }
    return values;
}

void ICookie::setCookie(const QString &key, const QString &value)
{
    ICookiePart part;
    part.key = key;
    part.value = value;
    raw->m_responseCookies.append(part);
}

$PackageWebCoreEnd
