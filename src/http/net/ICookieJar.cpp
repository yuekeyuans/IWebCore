#include "ICookieJar.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IRequestImpl.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

const QMultiHash<IStringView, IStringView> &ICookieJar::requestCookies() const
{
    return m_impl.m_reqRaw.m_cookies;
}

ICookiePart ICookieJar::getRequestCookie(IString key) const
{
    auto value = m_impl.m_reqRaw.m_cookies.value(key);
    if(value.length() == 0){
        return {};
    }
    return {key, value};
}

QList<ICookiePart> ICookieJar::getRequestCookies(const IString &key) const
{
    QList<ICookiePart> cookies;
    auto values = m_impl.m_reqRaw.m_cookies.values(key);
    for(auto value : values){
        cookies.append({key, value});
    }
    return cookies;
}

IStringViewList ICookieJar::requestCookieKeys() const
{
    return m_impl.m_reqRaw.m_cookies.keys();
}

bool ICookieJar::containRequestCookieKey(const IString& key) const
{
    return m_impl.m_reqRaw.m_cookies.contains(key);
}

//bool ICookieJar::containRequestCookieKey(const  &key) const
//{
//    auto temp = key.toUtf8();
//    return containRequestCookieKey(IStringView(temp));
//}

void ICookieJar::deleteRequestCookies(const IString& key)
{
    auto values = m_impl.m_reqRaw.m_cookies.values(key);
    for(auto value : values){
        ICookiePart part(key, value, 0);
        addResponseCookie(part);
    }
}

//void ICookieJar::deleteRequestCookies(const QString &key)
//{
//    auto temp = key.toUtf8();
//    return deleteRequestCookies(IStringView(temp));
//}

std::list<ICookiePart> &ICookieJar::responseCookies()
{
    return m_impl.m_respRaw.m_cookies;
}

const std::list<ICookiePart> &ICookieJar::responseCookies() const
{
    return m_impl.m_respRaw.m_cookies;
}

ICookiePart ICookieJar::getResponseCookie(const IString &key) const
{
    const auto& cookies = m_impl.m_respRaw.m_cookies;
    for(auto it=cookies.cbegin(); it!=cookies.cend(); it++){
        if(it->m_key == key){
            return *it;
        }
    }
    return {};
}

QList<IString> ICookieJar::responseCookieKeys() const
{
    const auto& cookies = m_impl.m_respRaw.m_cookies;
    QList<IString> keys;
    for(const auto& part : cookies){
        keys.append(part.m_key);
    }
    return keys;
}

bool ICookieJar::containResponseCookieKey(const IString &key) const
{
    const auto& cookies = m_impl.m_respRaw.m_cookies;
    for(const auto& part : cookies){
        if(part.m_key == key){
            return true;
        }
    }
    return false;
}

void ICookieJar::deleteResponseCookie(const IString &key)
{
    auto& cookies = m_impl.m_respRaw.m_cookies;
    for(auto it=cookies.begin(); it!= cookies.end();){
        if(it->m_key == key){
            it = cookies.erase(it);
        }else{
            it++;
        }
    }
}

void ICookieJar::addResponseCookie(ICookiePart cookiePart)
{
    m_impl.m_respRaw.m_cookies.push_back(std::move(cookiePart));
}

void ICookieJar::addResponseCookie(IString key, IString value)
{
    m_impl.m_respRaw.m_cookies.push_back({std::move(key), std::move(value)});
}

void ICookieJar::addResponseCookie(IString key, IString value, int maxAge, bool secure, bool httpOnly)
{
    m_impl.m_respRaw.m_cookies.push_back(ICookiePart{std::move(key), std::move(value), maxAge, secure, httpOnly});
}

void ICookieJar::addResponseCookie(IString key, IString value, QDateTime expires, bool secure, bool httpOnly)
{
    m_impl.m_respRaw.m_cookies.push_back(ICookiePart{std::move(key), std::move(value), std::move(expires), secure, httpOnly});
}

$PackageWebCoreEnd
