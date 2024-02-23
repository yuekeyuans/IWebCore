#include "ICookieJar.h"
#include "web/net/impl/IReqRespRaw.h"
#include "web/IWebAssert.h"
#include "core/base/IToeUtil.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

ICookieJar::ICookieJar() : IJarUnit(nullptr)
{
    $Ast->fatal("ICookieJar_CREATE_ERROR");
}

const QList<QPair<QString, QString> > &ICookieJar::requestCookies() const
{
    return m_raw->m_requestCookieParameters;
}

// this function is used to return one cookie-part, but when not one part found, the *ok is false
ICookiePart ICookieJar::getRequestCookie(const QString &key, bool& ok) const
{
    ICookiePart cookie;
    int count = 0;

    auto& cookies = m_raw->m_requestCookieParameters;
    for(const auto& pair : cookies){
        if(pair.first == key){
            count ++;
            cookie = {pair.first, pair.second};
        }
    }

    IToeUtil::setOk(ok, count == 1);
    return cookie;
}

QList<ICookiePart> ICookieJar::getRequestCookies(const QString &key) const
{
    QList<ICookiePart> ret;

    auto& cookies = m_raw->m_requestCookieParameters;
    for(const auto& pair : cookies){
        if(pair.first == key){
            ret.append({pair.first, pair.second});
        }
    }

    return ret;
}

QStringList ICookieJar::requestCookieKeys() const
{
    const auto& cookies = m_raw->m_requestCookieParameters;
    QStringList keys;
    for(const auto& cookie : cookies){
        keys.append(cookie.first);
    }
    return keys;
}

bool ICookieJar::containRequestCookieKey(const QString &key) const
{
    for(const auto& pair  : m_raw->m_requestCookieParameters){
        if(pair.first == key){
            return true;
        }
    }
    return false;
}

QString ICookieJar::getRequestCookieValue(const QString &key, bool &ok) const
{
    QString ret;

    int count{0};
    for(const auto& pair  : m_raw->m_requestCookieParameters){
        if(pair.first == key){
            count ++;
            ret = pair.second;
        }
    }
    IToeUtil::setOk(ok, count == 1);
    return ret;
}

QStringList ICookieJar::getRequestCookieValues(const QString &key) const
{
    QStringList ret;

    for(const auto& pair  : m_raw->m_requestCookieParameters){
        if(pair.first == key){
            ret.append(pair.second);
        }
    }
    return ret;
}

void ICookieJar::deleteRequestCookies(const QString &key)
{
    auto values = getRequestCookieValues(key);
    for(const auto& value : values){
        ICookiePart part(key, value, 0);
        addResponseCookie(part);
    }
}

QList<ICookiePart> &ICookieJar::responseCookies()
{
    return m_raw->m_responseCookies;
}

const QList<ICookiePart> &ICookieJar::responseCookies() const
{
    return m_raw->m_responseCookies;
}

ICookiePart &ICookieJar::getResponseCookie(const QString &key, bool& ok)
{
    auto& cookies = m_raw->m_responseCookies;
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
    auto& cookies = m_raw->m_responseCookies;
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
    const auto& cookies = m_raw->m_responseCookies;
    QStringList keys;
    for(const auto& part : cookies){
        keys.append(part.key);
    }
    return keys;
}

bool ICookieJar::containResponseCookieKey(const QString &key) const
{
    const auto& cookies = m_raw->m_responseCookies;
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
    auto& cookies = m_raw->m_responseCookies;
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
    m_raw->m_responseCookies.append(cookiePart);
}

void ICookieJar::addResponseCookie(const QString &key, const QString &value)
{
    ICookiePart part;
    part.key = key;
    part.value = value;
    m_raw->m_responseCookies.append(part);
}

void ICookieJar::addResponseCookie(const QString &key, const QString &value, int maxAge, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, maxAge, secure, httpOnly);
    m_raw->m_responseCookies.append(part);
}

void ICookieJar::addResponseCookie(const QString &key, const QString &value, const QDateTime &expires, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, expires, secure, httpOnly);
    m_raw->m_responseCookies.append(part);
}

bool ICookieJar::isValid() const
{
    return m_raw != nullptr;
}

$PackageWebCoreEnd
