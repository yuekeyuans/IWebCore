#include "ICookiePart.h"
#include "core/util/IConvertUtil.h"
#include "http/biscuits/IHttpHeader.h"

$PackageWebCoreBegin

namespace ICookiePartHelper
{
    QString sameSiteTypeToString(ICookiePart::SameSiteType type);
}

ICookiePart::ICookiePart(IStringView key, IStringView value)
    : ICookiePart(key.toQString(), value.toQString())
{
}

ICookiePart::ICookiePart(QString key, QString value)
    : key(std::move(key)), value(std::move(value))
{
}

ICookiePart::ICookiePart(QString key, QString value, int maxAge, bool secure, bool httpOnly)
    : key(std::move(key)), value(std::move(value)), maxAge(maxAge), secure(secure), httpOnly(httpOnly)
{
}

ICookiePart::ICookiePart(QString key, QString value, QDateTime expires, bool secure, bool httpOnly)
    : key(std::move(key)), value(std::move(value)), expires(std::move(expires)), secure(secure), httpOnly(httpOnly)
{
}

ICookiePart::ICookiePart(IStringView key, IStringView value, int maxAge, bool secure, bool httpOnly)
    : ICookiePart(key.toQString(), value.toQString(), maxAge, secure, httpOnly)
{
}

ICookiePart::ICookiePart(IStringView key, IStringView value, QDateTime expires, bool secure, bool httpOnly)
    : ICookiePart(key.toQString(), value.toQString(), std::move(expires), secure, httpOnly)
{
}

ICookiePart &ICookiePart::setKey(QString key)
{
    this->key = std::move(key);
    return *this;
}

ICookiePart &ICookiePart::setValue(QString value)
{
    this->value = std::move(value);
    return *this;
}

ICookiePart &ICookiePart::setDomain(QString domain)
{
    this->domain = std::move(domain);
    return *this;
}

ICookiePart &ICookiePart::setPath(QString path)
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

// TODO:
QString ICookiePart::toHeaderString() const
{
    QString header;
    header.append(IHttpHeader::SetCookie.toQString()).append(": ")
        .append(key);
    if(!value.isEmpty()){
        header.append('=').append(value);
    }

    if(!domain.isEmpty()){
        header.append("; Domain=").append(domain);
    }

    if(!path.isEmpty()){
        header.append("; Path=").append(path);
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
