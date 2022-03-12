#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class ICookiePart
{
    Q_GADGET
public:
    enum SameSiteType{
        Lax,
        None,
        Strict
    };

    Q_ENUM(SameSiteType)

public:
    ICookiePart();

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

$PackageWebCoreEnd
