#include "ICookiePart.h"
#include "biscuits/IHttpHeader.h"
#include "base/IConvertUtil.h"

$PackageWebCoreBegin

ICookiePart::ICookiePart()
{
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
        header.append("; domain=").append(domain);
    }

    if(!path.isEmpty()){
        header.append("; path=").append(path);
    }

    if(maxAge != INT_MIN){               // see https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie#browser_compatibility
        header.append("; Max-Age=").append(QString::number(maxAge));
    }
    if(expires.isValid()){
        header.append("; Expires=").append(IConvertUtil::toUtcString(expires)); // TODO:
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
