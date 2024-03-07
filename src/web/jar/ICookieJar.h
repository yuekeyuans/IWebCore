#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "web/jar/ICookiePart.h"
#include "web/jar/IJarUnit.h"
#include <chrono>

$PackageWebCoreBegin

class ICookieJar : public IJarUnit, IRegisterMetaTypeUnit<ICookieJar>
{
public:
    using IJarUnit::IJarUnit;

public:
    ICookieJar();

    // request
    const QList<QPair<QString, QString>>& requestCookies() const;
    ICookiePart getRequestCookie(const QString& key, bool& ok) const;
    QList<ICookiePart> getRequestCookies(const QString& key) const;

    QStringList requestCookieKeys() const;
    bool containRequestCookieKey(const QString& key) const;
    QString getRequestCookieValue(const QString& key, bool& ok) const;
    QStringList getRequestCookieValues(const QString& key) const;

    void deleteRequestCookies(const QString& key);

    // response
    QList<ICookiePart>& responseCookies();
    const QList<ICookiePart>& responseCookies() const;
    ICookiePart& getResponseCookie(const QString& key, bool& ok);
    const ICookiePart& getResponseCookie(const QString& key, bool& ok) const;

    QStringList responseCookieKeys() const;
    bool containResponseCookieKey(const QString& key) const;
    QString getResponseCookieValue(const QString& key, bool& ok);

    void deleteResponseCookie(const QString& key);

    template<typename T>        // in latter c++14, you can pass 1h, 24h type.
    void addResponseCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    void addResponseCookie(const ICookiePart& cookiePart);
    void addResponseCookie(const QString& key, const QString& value);
    void addResponseCookie(const QString& key, const QString& value, int maxAge, bool secure=false, bool httpOnly=false);
    void addResponseCookie(const QString& key, const QString& value, const QDateTime& expires, bool secure=false, bool httpOnly=false);

    virtual bool isValid() const final;
};

template<typename T>
void ICookieJar::addResponseCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, duration, secure, httpOnly);
    addResponseCookie(part);
}

$PackageWebCoreEnd
