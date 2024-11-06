#include "ICookieJar.h"
//#include "core/util/IToeUtil.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IRequestRaw.h"

$PackageWebCoreBegin

ICookieJar::ICookieJar() : IJarUnit(nullptr)
{
    IGlobalAbort::abortUnVisibleMethod();
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
    auto temp = key.toUtf8();
    return getRequestCookie(IStringView(temp));
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
    auto temp = key.toUtf8();
    return getRequestCookies(IStringView(temp));
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
    auto temp = key.toUtf8();
    return containRequestCookieKey(IStringView(temp));
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
    auto temp = key.toUtf8();
    return deleteRequestCookies(IStringView(temp));
}

std::list<ICookiePart> &ICookieJar::responseCookies()
{
    return m_raw->m_responseRaw->cookies;
}

const std::list<ICookiePart> &ICookieJar::responseCookies() const
{
    return m_raw->m_responseRaw->cookies;
}

ICookiePart ICookieJar::getResponseCookie(const QString &key) const
{
    const auto& cookies = m_raw->m_responseRaw->cookies;
    for(auto it=cookies.cbegin(); it!=cookies.cend(); it++){
        if(it->key == key){
            return *it;
        }
    }
    return {};
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

void ICookieJar::addResponseCookie(ICookiePart cookiePart)
{
    m_raw->m_responseRaw->cookies.push_back(std::move(cookiePart));
}

void ICookieJar::addResponseCookie(QString key, QString value)
{
    m_raw->m_responseRaw->cookies.push_back({std::move(key), std::move(value)});
}

void ICookieJar::addResponseCookie(QString key, QString value, int maxAge, bool secure, bool httpOnly)
{
    m_raw->m_responseRaw->cookies.push_back(ICookiePart{std::move(key), std::move(value), maxAge, secure, httpOnly});
}

void ICookieJar::addResponseCookie(QString key, QString value, QDateTime expires, bool secure, bool httpOnly)
{
    m_raw->m_responseRaw->cookies.push_back(ICookiePart{std::move(key), std::move(value), std::move(expires), secure, httpOnly});
}

bool ICookieJar::isValid() const
{
    return m_raw != nullptr;
}

$PackageWebCoreEnd
