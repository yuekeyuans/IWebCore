#include "ICookieJar.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/IHttpAssert.h"
#include "core/base/IToeUtil.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

ICookieJar::ICookieJar() : IJarUnit(nullptr)
{
    qFatal(IConstantUtil::UnVisibleMethod);
}

const QMultiHash<IStringView, IStringView> &ICookieJar::requestCookies() const
{
    return m_raw->m_requestCookieParameters;
}

ICookiePart ICookieJar::getRequestCookie(IStringView key) const
{
    auto value = m_raw->m_requestCookieParameters.value(key);
    if(value.empty()){
        return {};
    }
    return {key, value};
}

ICookiePart ICookieJar::getRequestCookie(const QString &key) const
{
    return getRequestCookie(key.toStdString());
}

QList<ICookiePart> ICookieJar::getRequestCookies(IStringView key) const
{
    QList<ICookiePart> cookies;
    auto values = m_raw->m_requestCookieParameters.values(key);
    for(auto value : values){
        cookies.append({key, value});
    }
    return cookies;
}

QList<ICookiePart> ICookieJar::getRequestCookies(const QString &key) const
{
    return getRequestCookies(key.toStdString());
}

IStringViewList ICookieJar::requestCookieKeys() const
{
    return m_raw->m_requestCookieParameters.keys();
}

bool ICookieJar::containRequestCookieKey(IStringView key) const
{
    return m_raw->m_requestCookieParameters.contains(key);
}

bool ICookieJar::containRequestCookieKey(const QString &key) const
{
    return containRequestCookieKey(key.toStdString());
}

void ICookieJar::deleteRequestCookies(IStringView key)
{
    auto values = m_raw->m_requestCookieParameters.values(key);
    for(auto value : values){
        ICookiePart part(key, value, 0);
        addResponseCookie(part);
    }
}

void ICookieJar::deleteRequestCookies(const QString &key)
{
    return deleteRequestCookies(key.toStdString());
}

QList<ICookiePart> &ICookieJar::responseCookies()
{
    return m_raw->m_responseRaw->cookies;
}

const QList<ICookiePart> &ICookieJar::responseCookies() const
{
    return m_raw->m_responseRaw->cookies;
}

ICookiePart &ICookieJar::getResponseCookie(const QString &key, bool& ok)
{
    auto& cookies = m_raw->m_responseRaw->cookies;
    for(auto it=cookies.begin(); it!=cookies.end(); it++){
        if(it->key == key){
            IToeUtil::setOk(ok, true);
            return *it;
        }
    }
    IToeUtil::setOk(ok, false);
    return *cookies.end();
}

const ICookiePart &ICookieJar::getResponseCookie(const QString &key, bool& ok) const
{
    auto& cookies = m_raw->m_responseRaw->cookies;
    for(auto it=cookies.begin(); it!=cookies.end(); it++){
        if(it->key == key){
            IToeUtil::setOk(ok, true);
            return *it;
        }
    }
    IToeUtil::setOk(ok, false);
    return *cookies.end();
}

QStringList ICookieJar::responseCookieKeys() const
{
    const auto& cookies = m_raw->m_responseRaw->cookies;
    QStringList keys;
    for(const auto& part : cookies){
        keys.append(part.key);
    }
    return keys;
}

bool ICookieJar::containResponseCookieKey(const QString &key) const
{
    const auto& cookies = m_raw->m_responseRaw->cookies;
    for(const auto& part : cookies){
        if(part.key == key){
            return true;
        }
    }
    return false;
}

QString ICookieJar::getResponseCookieValue(const QString &key, bool& ok)
{
    const auto& cookie = getResponseCookie(key, ok);
    if(ok){
        return cookie.value;
    }

    return {};
}

void ICookieJar::deleteResponseCookie(const QString &key)
{
    auto& cookies = m_raw->m_responseRaw->cookies;
    for(auto it=cookies.begin(); it!= cookies.end();){
        if(it->key == key){
            it = cookies.erase(it);
        }else{
            it++;
        }
    }
}

void ICookieJar::addResponseCookie(const ICookiePart &cookiePart)
{
    m_raw->m_responseRaw->cookies.append(cookiePart);
}

void ICookieJar::addResponseCookie(const QString &key, const QString &value)
{
    ICookiePart part;
    part.key = key;
    part.value = value;
    m_raw->m_responseRaw->cookies.append(part);
}

void ICookieJar::addResponseCookie(const QString &key, const QString &value, int maxAge, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, maxAge, secure, httpOnly);
    m_raw->m_responseRaw->cookies.append(part);
}

void ICookieJar::addResponseCookie(const QString &key, const QString &value, const QDateTime &expires, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, expires, secure, httpOnly);
    m_raw->m_responseRaw->cookies.append(part);
}

bool ICookieJar::isValid() const
{
    return m_raw != nullptr;
}

$PackageWebCoreEnd
