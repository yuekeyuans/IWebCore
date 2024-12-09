#include "ICookiePart.h"
#include "core/util/IConvertUtil.h"
#include "core/util/IConstantUtil.h"
#include "http/biscuits/IHttpHeader.h"

$PackageWebCoreBegin

namespace detail
{
    const IString& sameSiteTypeToString(ICookiePart::SameSiteType type);
}

ICookiePart::ICookiePart(IString key_, IString value_)
    : key(std::move(key_)), value(std::move(value_))
{
}

ICookiePart::ICookiePart(IString key, IString value, int maxAge, bool secure, bool httpOnly)
    : key(std::move(key)), value(std::move(value)), maxAge(maxAge), secure(secure), httpOnly(httpOnly)
{
}

ICookiePart::ICookiePart(IString key, IString value, QDateTime expires, bool secure, bool httpOnly)
    : key(std::move(key)), value(std::move(value)), expires(std::move(expires)), secure(secure), httpOnly(httpOnly)
{
}

ICookiePart &ICookiePart::setKey(IString key)
{
    this->key = std::move(key);
    return *this;
}

ICookiePart &ICookiePart::setValue(IString value)
{
    this->value = std::move(value);
    return *this;
}

ICookiePart &ICookiePart::setDomain(IString domain)
{
    this->domain = std::move(domain);
    return *this;
}

ICookiePart &ICookiePart::setPath(IString path)
{
    this->path = std::move(path);
    return *this;
}

ICookiePart &ICookiePart::setExpires(QDateTime dateTime)
{
    this->expires = std::move(dateTime);
    return *this;
}

ICookiePart &ICookiePart::setMaxAge(int maxAge)
{
    this->maxAge = maxAge;
    return *this;
}

ICookiePart &ICookiePart::setSecure(bool secure)
{
    this->secure = secure;
    return *this;
}

ICookiePart &ICookiePart::setHttpOnly(bool httpOnly)
{
    this->httpOnly = httpOnly;
    return *this;
}

ICookiePart &ICookiePart::setSameSite(ICookiePart::SameSiteType sameSite)
{
    this->sameSite = sameSite;
    return *this;
}

std::vector<IStringView> ICookiePart::toHeaderString() const
{
    static const IString DomainIString = "; Domain=";
    static const IString PathIString = "; Path=";
    static const IString MaxAgeIString = "; Max-Age=";
    static const IString ExpiresIString = "; Expires=";
    static const IString SameSiteIString = "; SameSite=";
    static const IString SecureIString = "; Secure";
    static const IString HttpOnlyIString = "; HttpOnly";

    std::vector<IStringView> ret;
    if(key.isEmpty() || value.isEmpty()){
        return ret;
    }

    ret.push_back(IHttpHeader::SetCookie.m_stringView);
    ret.push_back(IConstantUtil::Comma.m_stringView);
    ret.push_back(key.m_stringView);
    ret.push_back(IConstantUtil::Equal.m_stringView);
    ret.push_back(value.m_stringView);

    if(!domain.isEmpty()){
        ret.push_back(DomainIString.m_stringView);
        ret.push_back(domain.m_stringView);
    }
    if(!path.isEmpty()){
        ret.push_back(PathIString.m_stringView);
        ret.push_back(path.m_stringView);
    }
    if(maxAge != std::numeric_limits<int>::min()){               // see https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie#browser_compatibility
        m_maxAgeString = std::to_string(maxAge);
        ret.push_back(MaxAgeIString.m_stringView);
        ret.push_back(IString(&m_maxAgeString).m_stringView);
    }
    if(expires.isValid()){
        m_expiresString = IConvertUtil::toUtcString(expires).toStdString();
        ret.push_back(ExpiresIString.m_stringView);
        ret.push_back(IString(&m_expiresString).m_stringView);
    }
    if(sameSite != Lax){
        ret.push_back(SameSiteIString.m_stringView);
        ret.push_back(detail::sameSiteTypeToString(sameSite).m_stringView);
    }
    if(secure){
        ret.push_back(SecureIString.m_stringView);
    }
    if(httpOnly){
        ret.push_back(HttpOnlyIString.m_stringView);
    }

    ret.push_back(IConstantUtil::NewLine.m_stringView);
    return ret;
}

bool ICookiePart::isValid()
{
    if(key.isEmpty()){
        return false;
    }
    if(maxAge != -1 && expires.isValid()){
        return false;
    }
    return true;
}

const IString& detail::sameSiteTypeToString(ICookiePart::SameSiteType type)
{
    static const std::vector<IString> strings {
        "Lax",
        "None",
        "Strict"
    };
    return strings[static_cast<int>(type)];
}

$PackageWebCoreEnd
