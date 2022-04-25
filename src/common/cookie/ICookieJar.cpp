#include "ICookieJar.h"
#include "common/net/impl/IReqRespRaw.h"

#include "base/IToeUtil.h"

$PackageWebCoreBegin

QStringList ICookieJar::requestCookieKeys() const
{
    const auto& cookies = raw->m_requestCookieParameters;
    QStringList keys;
    for(const auto& cookie : cookies){
        keys.append(cookie.first);
    }
    return keys;
}

QStringList ICookieJar::requestCookieValues() const
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

void ICookieJar::deleteRequestCookie(const QString &key)
{
    bool ok;
    auto value = getRequestCookieValue(key, &ok);
    if(ok){
        ICookiePart part(key, value, -1);
        addResponseCookie(part);
    }
}

bool ICookieJar::hasRequestCookie(const QString &key) const
{
    for(const auto& pair  : raw->m_requestCookieParameters){
        if(pair.first == key){
            return true;
        }
    }
    return false;
}

QString ICookieJar::getRequestCookieValue(const QString &key, bool *ok)
{
    for(const auto& pair  : raw->m_requestCookieParameters){
        if(pair.first == key){
            IToeUtil::setOk(ok, true);
            return pair.second;
        }
    }
    IToeUtil::setOk(ok, false);
    return "";
}

inline const QList<QPair<QString, QString> > &ICookieJar::requestCookies() const
{
    return raw->m_requestCookieParameters;
}

QStringList ICookieJar::responseCookieKeys() const
{
    const auto& cookies = raw->m_responseCookies;
    QStringList keys;
    for(const auto& part : cookies){
        keys.append(part.key);
    }
    return keys;
}

QStringList ICookieJar::responseCookieValues() const
{
    const auto& cookies = raw->m_responseCookies;
    QStringList keys;
    for(const auto& part : cookies){
        keys.append(part.value);
    }
    return keys;
}

inline QList<ICookiePart> &ICookieJar::responseCookies()
{
    return raw->m_responseCookies;
}

inline const QList<ICookiePart> &ICookieJar::responseCookies() const
{
    return raw->m_responseCookies;
}

bool ICookieJar::hasResponseCookie(const QString &key) const
{
    const auto& cookies = raw->m_responseCookies;
    for(const auto& part : cookies){
        if(part.key == key){
            return true;
        }
    }
    return false;
}

ICookiePart &ICookieJar::getResponseCookie(const QString &key, bool *ok)
{
    auto& cookies = raw->m_responseCookies;
    for(auto it=cookies.begin(); it!=cookies.end(); it++){
        if(it->key == key){
            IToeUtil::setOk(ok, true);
            return *it;
        }
    }
    IToeUtil::setOk(ok, false);
    return *cookies.end();
}

const ICookiePart &ICookieJar::getResponseCookie(const QString &key, bool *ok) const
{
    auto& cookies = raw->m_responseCookies;
    for(auto it=cookies.begin(); it!=cookies.end(); it++){
        if(it->key == key){
            IToeUtil::setOk(ok, true);
            return *it;
        }
    }
    IToeUtil::setOk(ok, false);
    return *cookies.end();
}

inline void ICookieJar::addResponseCookie(const ICookiePart &cookiePart)
{
    raw->m_responseCookies.append(cookiePart);
}

void ICookieJar::addResponseCookie(const QString &key, const QString &value)
{
    ICookiePart part;
    part.key = key;
    part.value = value;
    raw->m_responseCookies.append(part);
}

void ICookieJar::addResponseCookie(const QString &key, const QString &value, int maxAge, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, maxAge, secure, httpOnly);
    raw->m_responseCookies.append(part);
}

void ICookieJar::addResponseCookie(const QString &key, const QString &value, const QDateTime &expires, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, expires, secure, httpOnly);
    raw->m_responseCookies.append(part);
}

void ICookieJar::deleteResponseCookie(const QString &key)
{
    auto& cookies = raw->m_responseCookies;
    for(auto it=cookies.begin(); it!= cookies.end();){
        if(it->key == key){
            it = cookies.erase(it);
        }else{
            it++;
        }
    }
}

$PackageWebCoreEnd
