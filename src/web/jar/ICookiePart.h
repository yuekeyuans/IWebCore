#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "base/IPreProcessorUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

// TODO: 这里 cookiePart 是否能够像  IMultiPart 一样注入到 函数参数当中？

class ICookiePart : public IRegisterMetaTypeUnit<ICookiePart>
{
    Q_GADGET
    $UseMetaRegistration(ICookiePart);
public:
    enum SameSiteType{
        Lax,
        None,
        Strict
    };

    Q_ENUM(SameSiteType)

public:
    ICookiePart() = default;

    template<typename T>
    explicit ICookiePart(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);

    explicit ICookiePart(const QString& key, const QString& value, int maxAge, bool secure=false, bool httpOnly=false);

    explicit ICookiePart(const QString& key, const QString& value, const QDateTime& expires, bool secure=false, bool httpOnly=false);

public:
    ICookiePart& setKey(const QString& key);
    ICookiePart& setValue(const QString& value);
    ICookiePart& setDomain(const QString& domain);
    ICookiePart& setPath(const QString& path);
    ICookiePart& setExpires(const QDateTime& dateTime);
    ICookiePart& setMaxAge(int maxAge);
    ICookiePart& setSecure(bool secure);
    ICookiePart& setHttpOnly(bool httpOnly);
    ICookiePart& setSameSite(SameSiteType sameSite);

    QString toHeaderString();

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
ICookiePart::ICookiePart(const QString &key, const QString &value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
    : ICookiePart(key, value,std::chrono::duration_cast<std::chrono::seconds>(duration).count(), secure, httpOnly)
{
}

$PackageWebCoreEnd
