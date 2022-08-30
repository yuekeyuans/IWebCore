#include "ICookiePart.h"
#include "base/IConvertUtil.h"
#include "web/biscuits/IHttpHeader.h"

$PackageWebCoreBegin

ICookiePart::ICookiePart(const QString &key, const QString &value, int maxAge, bool secure, bool httpOnly)
{
    this->key = key;
    this->value = value;
    this->maxAge = maxAge;
    this->secure = secure;
    this->httpOnly = httpOnly;
}

ICookiePart::ICookiePart(const QString &key, const QString &value, const QDateTime &expires, bool secure, bool httpOnly)
{
    this->key = key;
    this->value = value;
    this->expires = expires;
    this->secure = secure;
    this->httpOnly = httpOnly;
}

ICookiePart &ICookiePart::setKey(const QString &key)
{
    this->key = key;
    return *this;
}

ICookiePart &ICookiePart::setValue(const QString &value)
{
    this->value = value;
    return *this;
}

ICookiePart &ICookiePart::setDomain(const QString &domain)
{
    this->domain = domain;
    return *this;
}

ICookiePart &ICookiePart::setPath(const QString &path)
{
    this->path = path;
    return *this;
}

ICookiePart &ICookiePart::setExpires(const QDateTime &dateTime)
{
    this->expires = dateTime;
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

QString ICookiePart::toHeaderString()
{
    QString header;
    header.append(IHttpHeader::SetCookie).append(": ")
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
        header.append("; SameSite=").append(QMetaEnum::fromType<ICookiePart::SameSiteType>().valueToKey(sameSite));
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

$PackageWebCoreEnd
