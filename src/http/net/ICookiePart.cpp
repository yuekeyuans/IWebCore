#include "ICookiePart.h"
#include "core/util/IConvertUtil.h"
#include "http/biscuits/IHttpHeader.h"

$PackageWebCoreBegin

namespace ICookiePartHelper
{
    QString sameSiteTypeToString(ICookiePart::SameSiteType type);
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

// TODO: 这个优化一下，之后
QString ICookiePart::toHeaderString() const
{
    QString header;
    header.append(IHttpHeader::SetCookie.m_stringView.toQString()).append(": ")
        .append(key.m_stringView.toQString());
    if(!value.isEmpty()){
        header.append('=').append(value.m_stringView.toQString());
    }

    if(!domain.isEmpty()){
        header.append("; Domain=").append(domain.m_stringView.toQString());
    }

    if(!path.isEmpty()){
        header.append("; Path=").append(path.m_stringView.toQString());
    }

    if(maxAge != INT_MIN){               // see https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie#browser_compatibility
        header.append("; Max-Age=").append(QString::number(maxAge));
    }
    if(expires.isValid()){
        header.append("; Expires=").append(IConvertUtil::toUtcString(expires));
    }

    if(sameSite != Lax){
        header.append("; SameSite=").append(ICookiePartHelper::sameSiteTypeToString(sameSite));
    }
    if(secure){
        header.append("; Secure");
    }
    if(httpOnly){
        header.append("; HttpOnly");
    }

    return header;
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

QString ICookiePartHelper::sameSiteTypeToString(ICookiePart::SameSiteType type)
{
    static const QStringList strings {
        "Lax",
        "None",
        "Strict"
    };
    return strings[static_cast<int>(type)];
}

$PackageWebCoreEnd
