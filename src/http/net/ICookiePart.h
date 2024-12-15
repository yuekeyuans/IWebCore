#pragma once

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
    ICookiePart(IString m_key, IString m_value);

    template<typename T>
    explicit ICookiePart(IString key, IString value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    explicit ICookiePart(IString key, IString value, int maxAge, bool secure=false, bool httpOnly=false);
    explicit ICookiePart(IString key, IString value, QDateTime expires, bool secure=false, bool httpOnly=false);

public:
    ICookiePart& setKey(IString m_key);
    ICookiePart& setValue(IString m_value);
    ICookiePart& setDomain(IString m_domain);
    ICookiePart& setPath(IString m_path);
    ICookiePart& setExpires(QDateTime dateTime);
    ICookiePart& setMaxAge(int m_maxAge);
    ICookiePart& setSecure(bool m_secure);
    ICookiePart& setHttpOnly(bool m_httpOnly);
    ICookiePart& setSameSite(SameSiteType m_sameSite);

    std::vector<IStringView> toHeaderString() const;

    bool isValid();

public:
    IString m_key;
    IString m_value;
    IString m_domain;
    IString m_path;

    QDateTime m_expires {};
    int m_maxAge {std::numeric_limits<int>::min()};

    bool m_secure {false};
    bool m_httpOnly {false};
    SameSiteType m_sameSite{Lax};

private:
    mutable std::string m_maxAgeString; // TODO: 这个不是最优解
    mutable std::string m_expiresString;

public:
    static const ICookiePart Empty;
};

template<typename T>
ICookiePart::ICookiePart(IString key, IString value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
    : ICookiePart(std::move(key), std::move(value), std::chrono::duration_cast<std::chrono::seconds>(duration).count(), secure, httpOnly)
{
}

$PackageWebCoreEnd
