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

const QMultiHash<QString, QString> &ICookieJar::requestCookies() const
{
    return m_raw->m_requestCookieParameters;
}

// this function is used to return one cookie-part, but when not one part found, the *ok is false
ICookiePart ICookieJar::getRequestCookie(const QString &key, bool& ok) const
{
    auto values = m_raw->m_requestCookieParameters.values(key);
    IToeUtil::setOk(ok, values.length() == 1);
    if(values.length() > 0){
        return {key, values.first()};
    }
    return {};
}


QList<ICookiePart> ICookieJar::getRequestCookies(const QString &key) const
{
    QList<ICookiePart> ret;

    auto values = m_raw->m_requestCookieParameters.values(key);
    for(const auto& value : values){
        ret.append({key, value});
    }

    return ret;
}

QStringList ICookieJar::requestCookieKeys() const
{
    return m_raw->m_requestCookieParameters.keys();
}

bool ICookieJar::containRequestCookieKey(const QString &key) const
{
    return m_raw->m_requestCookieParameters.contains(key);
}

//QString ICookieJar::getRequestCookieValue(const QString &key, bool &ok) const
//{
//    QString ret;

//    int count{0};
//    for(const auto& pair  : m_raw->m_requestCookieParameters){
//        if(pair.first == key){
//            count ++;
//            ret = pair.second;
//        }
//    }
//    IToeUtil::setOk(ok, count == 1);
//    return ret;
//}

//QStringList ICookieJar::getRequestCookieValues(const QString &key) const
//{
//    QStringList ret;

//    for(const auto& pair  : m_raw->m_requestCookieParameters){
//        if(pair.first == key){
//            ret.append(pair.second);
//        }
//    }
//    return ret;
//}

void ICookieJar::deleteRequestCookies(const QString &key)
{
    auto values = m_raw->m_requestCookieParameters.values(key);
    for(const auto& value : values){
        ICookiePart part(key, value, 0);
        addResponseCookie(part);
    }
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
