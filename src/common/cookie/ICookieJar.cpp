#include "ICookieJar.h"
#include "common/net/impl/IReqRespRaw.h"

#include "base/IToeUtil.h"

$PackageWebCoreBegin

const QList<QPair<QString, QString> > &ICookieJar::requestCookies() const
{
    return raw->m_requestCookieParameters;
}

QList<QPair<QString, QString> > &ICookieJar::requestCookies()
{
    return raw->m_requestCookieParameters;
}

QStringList ICookieJar::requestCookieKeys() const
{
    const auto& cookies = raw->m_requestCookieParameters;
    QStringList keys;
    for(const auto& cookie : cookies){
        keys.append(cookie.first);
    }
    return keys;
}

bool ICookieJar::containRequestCookie(const QString &key) const
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

void ICookieJar::deleteRequestCookie(const QString &key)
{
    bool ok;
    auto value = getRequestCookieValue(key, &ok);
    if(ok){
        ICookiePart part(key, value, -1);
        addResponseCookie(part);
    }
}

QList<ICookiePart> &ICookieJar::responseCookies()
{
    return raw->m_responseCookies;
}

const QList<ICookiePart> &ICookieJar::responseCookies() const
{
    return raw->m_responseCookies;
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

void ICookieJar::addResponseCookie(const ICookiePart &cookiePart)
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

bool ICookieJar::isValid() const
{
    return raw != nullptr;
}

$PackageWebCoreEnd
