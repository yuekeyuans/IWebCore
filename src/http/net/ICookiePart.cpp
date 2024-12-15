#include "ICookiePart.h"
#include "core/util/IConvertUtil.h"
#include "core/util/IConstantUtil.h"
#include "http/biscuits/IHttpHeader.h"

$PackageWebCoreBegin

const ICookiePart ICookiePart::Empty;

namespace detail
{
    const IString& sameSiteTypeToString(ICookiePart::SameSiteType type);
}

ICookiePart::ICookiePart(IString key, IString value)
    : m_key(std::move(key)), m_value(std::move(value))
{
}

ICookiePart::ICookiePart(IString key, IString value, int maxAge, bool secure, bool httpOnly)
    : m_key(std::move(key)), m_value(std::move(value)), m_maxAge(maxAge), m_secure(secure), m_httpOnly(httpOnly)
{
}

ICookiePart::ICookiePart(IString key, IString value, QDateTime expires, bool secure, bool httpOnly)
    : m_key(std::move(key)), m_value(std::move(value)), m_expires(std::move(expires)), m_secure(secure), m_httpOnly(httpOnly)
{
}

ICookiePart &ICookiePart::setKey(IString key)
{
    this->m_key = std::move(key);
    return *this;
}

ICookiePart &ICookiePart::setValue(IString value)
{
    this->m_value = std::move(value);
    return *this;
}

ICookiePart &ICookiePart::setDomain(IString domain)
{
    this->m_domain = std::move(domain);
    return *this;
}

ICookiePart &ICookiePart::setPath(IString path)
{
    this->m_path = std::move(path);
    return *this;
}

ICookiePart &ICookiePart::setExpires(QDateTime dateTime)
{
    this->m_expires = std::move(dateTime);
    return *this;
}

ICookiePart &ICookiePart::setMaxAge(int maxAge)
{
    this->m_maxAge = maxAge;
    return *this;
}

ICookiePart &ICookiePart::setSecure(bool secure)
{
    this->m_secure = secure;
    return *this;
}

ICookiePart &ICookiePart::setHttpOnly(bool httpOnly)
{
    this->m_httpOnly = httpOnly;
    return *this;
}

ICookiePart &ICookiePart::setSameSite(ICookiePart::SameSiteType sameSite)
{
    this->m_sameSite = sameSite;
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
    if(m_key.isEmpty() || m_value.isEmpty()){
        return ret;
    }

    ret.push_back(IHttpHeader::SetCookie.m_stringView);
    ret.push_back(IConstantUtil::Comma.m_stringView);
    ret.push_back(m_key.m_stringView);
    ret.push_back(IConstantUtil::Equal.m_stringView);
    ret.push_back(m_value.m_stringView);

    if(!m_domain.isEmpty()){
        ret.push_back(DomainIString.m_stringView);
        ret.push_back(m_domain.m_stringView);
    }
    if(!m_path.isEmpty()){
        ret.push_back(PathIString.m_stringView);
        ret.push_back(m_path.m_stringView);
    }
    if(m_maxAge != std::numeric_limits<int>::min()){               // see https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie#browser_compatibility
        m_maxAgeString = std::to_string(m_maxAge);
        ret.push_back(MaxAgeIString.m_stringView);
        ret.push_back(IString(&m_maxAgeString).m_stringView);
    }
    if(m_expires.isValid()){
        m_expiresString = IConvertUtil::toUtcString(m_expires).toStdString();
        ret.push_back(ExpiresIString.m_stringView);
        ret.push_back(IString(&m_expiresString).m_stringView);
    }
    if(m_sameSite != Lax){
        ret.push_back(SameSiteIString.m_stringView);
        ret.push_back(detail::sameSiteTypeToString(m_sameSite).m_stringView);
    }
    if(m_secure){
        ret.push_back(SecureIString.m_stringView);
    }
    if(m_httpOnly){
        ret.push_back(HttpOnlyIString.m_stringView);
    }

    ret.push_back(IConstantUtil::NewLine.m_stringView);
    return ret;
}

bool ICookiePart::isValid()
{
    if(m_key.isEmpty()){
        return false;
    }
    if(m_maxAge != -1 && m_expires.isValid()){
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
