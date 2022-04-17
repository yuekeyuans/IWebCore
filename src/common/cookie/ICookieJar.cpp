#include "ICookieJar.h"
#include "common/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

QStringList ICookieJar::keys()
{
    const auto& cookies = raw->m_requestCookieParameters;
    QStringList keys;
    for(const auto& cookie : cookies){
        keys.append(cookie.first);
    }
    return keys;
}

QStringList ICookieJar::values()
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

void ICookieJar::addCookie(const ICookiePart &cookiePart)
{
    raw->m_responseCookies.append(cookiePart);
}

void ICookieJar::addCookie(const QString &key, const QString &value)
{
    ICookiePart part;
    part.key = key;
    part.value = value;
    raw->m_responseCookies.append(part);
}

void ICookieJar::addCookie(const QString &key, const QString &value, int maxAge, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, maxAge, secure, httpOnly);
    raw->m_responseCookies.append(part);
}

void ICookieJar::addCookie(const QString &key, const QString &value, const QDateTime &expires, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, expires, secure, httpOnly);
    raw->m_responseCookies.append(part);
}

$PackageWebCoreEnd
