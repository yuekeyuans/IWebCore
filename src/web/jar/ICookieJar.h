﻿#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "web/jar/ICookiePart.h"
#include "web/jar/IJarUnit.h"
#include <chrono>

$PackageWebCoreBegin

class ICookieJar : public IJarUnit, IRegisterMetaTypeUnit<ICookieJar>
{
    Q_GADGET
    $UseMetaRegistration(ICookieJar)
public:
    using IJarUnit::IJarUnit;

public:
    ICookieJar();
    // request
    const QList<QPair<QString, QString>>& requestCookies() const;
    QList<QPair<QString, QString>>& requestCookies();

    QStringList requestCookieKeys() const;
    bool containRequestCookie(const QString& key) const;

    QString getRequestCookieValue(const QString&key, bool* ok);

    void deleteRequestCookie(const QString& key);

    // response
    QList<ICookiePart>& responseCookies();
    const QList<ICookiePart>& responseCookies() const;

    QStringList responseCookieKeys() const;
    bool hasResponseCookie(const QString& key) const;

    ICookiePart& getResponseCookie(const QString& key, bool *ok);
    const ICookiePart& getResponseCookie(const QString& key, bool* ok) const;

    template<typename T>        // in latter c++14, you can pass 1h, 24h type.
    void addResponseCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    void addResponseCookie(const ICookiePart& cookiePart);
    void addResponseCookie(const QString& key, const QString& value);
    void addResponseCookie(const QString& key, const QString& value, int maxAge, bool secure=false, bool httpOnly=false);
    void addResponseCookie(const QString& key, const QString& value, const QDateTime& expires, bool secure=false, bool httpOnly=false);

    void deleteResponseCookie(const QString& key);  // NOTE: 这个不是必须的,而且可能引起歧义.

    virtual bool isValid() const final;
};

template<typename T>
void ICookieJar::addResponseCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, duration, secure, httpOnly);
    addResponseCookie(part);
}

$PackageWebCoreEnd