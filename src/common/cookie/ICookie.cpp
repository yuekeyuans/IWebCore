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

void ICookie::setCookie(const ICookiePart &cookiePart)
{
    raw->m_responseCookies.append(cookiePart);
}

void ICookie::setCookie(const QString &key, const QString &value)
{
    ICookiePart part;
    part.key = key;
    part.value = value;
    raw->m_responseCookies.append(part);
}

void ICookie::setCookie(const QString &key, const QString &value, int maxAge, bool secure, bool httpOnly)
{
    ICookiePart part;
    part.key = key;
    part.value = value;
    part.maxAge = maxAge;
    part.secure = secure;
    part.httpOnly = httpOnly;
    raw->m_responseCookies.append(part);
}

void ICookie::setCookie(const QString &key, const QString &value, const QDateTime &expires, bool secure, bool httpOnly)
{
    ICookiePart part;
    part.key = key;
    part.value = value;
    part.expires = expires;
    part.secure = secure;
    part.httpOnly = httpOnly;
    raw->m_responseCookies.append(part);
}

$PackageWebCoreEnd
