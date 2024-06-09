#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

class ICookiePart : IRegisterMetaTypeUnit<ICookiePart>
{
public:
    enum SameSiteType{
        Lax,
        None,
        Strict
    };

public:
    ICookiePart() = default;
    ICookiePart(IStringView key, IStringView value);
    ICookiePart(QString key, QString value);

    template<typename T>
    explicit ICookiePart(QString key, QString value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    explicit ICookiePart(QString key, QString value, int maxAge, bool secure=false, bool httpOnly=false);
    explicit ICookiePart(QString key, QString value, QDateTime expires, bool secure=false, bool httpOnly=false);

    template<typename T>
    explicit ICookiePart(IStringView key, IStringView value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    explicit ICookiePart(IStringView key, IStringView value, int maxAge, bool secure=false, bool httpOnly=false);
    explicit ICookiePart(IStringView key, IStringView value, QDateTime expires, bool secure=false, bool httpOnly=false);

public:
    ICookiePart& setKey(QString key);
    ICookiePart& setValue(QString value);
    ICookiePart& setDomain(QString domain);
    ICookiePart& setPath(QString path);
    ICookiePart& setExpires(QDateTime dateTime);
    ICookiePart& setMaxAge(int maxAge);
    ICookiePart& setSecure(bool secure);
    ICookiePart& setHttpOnly(bool httpOnly);
    ICookiePart& setSameSite(SameSiteType sameSite);

    QString toHeaderString() const;

    bool isValid();

public:
    QString key;
    QString value;
    QString domain;
    QString path;

    QDateTime expires {};
    int maxAge {INT_MIN};

    bool secure {false};
    bool httpOnly {false};
    SameSiteType sameSite{Lax};
};

template<typename T>
ICookiePart::ICookiePart(QString key, QString value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
    : ICookiePart(std::move(key), std::move(value), std::chrono::duration_cast<std::chrono::seconds>(duration).count(), secure, httpOnly)
{
}

template<typename T>
ICookiePart::ICookiePart(IStringView key, IStringView value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
    : ICookiePart(key.toQString(), value.toQString(), std::chrono::duration_cast<std::chrono::seconds>(duration).count(), secure, httpOnly)
{
}

$PackageWebCoreEnd
