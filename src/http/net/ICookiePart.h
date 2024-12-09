﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

class ICookiePart
{
public:
    enum SameSiteType{
        Lax,
        None,
        Strict
    };

public:
    ICookiePart() = default;
    ICookiePart(IString key, IString value);

    template<typename T>
    explicit ICookiePart(IString key, IString value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    explicit ICookiePart(IString key, IString value, int maxAge, bool secure=false, bool httpOnly=false);
    explicit ICookiePart(IString key, IString value, QDateTime expires, bool secure=false, bool httpOnly=false);

public:
    ICookiePart& setKey(IString key);
    ICookiePart& setValue(IString value);
    ICookiePart& setDomain(IString domain);
    ICookiePart& setPath(IString path);
    ICookiePart& setExpires(QDateTime dateTime);
    ICookiePart& setMaxAge(int maxAge);
    ICookiePart& setSecure(bool secure);
    ICookiePart& setHttpOnly(bool httpOnly);
    ICookiePart& setSameSite(SameSiteType sameSite);

    std::vector<IStringView> toHeaderString() const;

    bool isValid();

public:
    IString key;
    IString value;
    IString domain;
    IString path;

    QDateTime expires {};
    int maxAge {std::numeric_limits<int>::min()};

    bool secure {false};
    bool httpOnly {false};
    SameSiteType sameSite{Lax};

private:
    mutable std::string m_maxAgeString; // TODO: 这个不是最优解
    mutable std::string m_expiresString;
};

template<typename T>
ICookiePart::ICookiePart(IString key, IString value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
    : ICookiePart(std::move(key), std::move(value), std::chrono::duration_cast<std::chrono::seconds>(duration).count(), secure, httpOnly)
{
}

$PackageWebCoreEnd
