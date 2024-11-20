#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/net/ICookiePart.h"
#include "http/net/IJarUnit.h"
#include <chrono>

$PackageWebCoreBegin

class ICookieJar : public IJarUnit, IRegisterMetaTypeUnit<ICookieJar>
{
public:
    using IJarUnit::IJarUnit;

public:
    ICookieJar();

    // request
    const QMultiHash<IStringView, IStringView>& requestCookies() const;
    ICookiePart getRequestCookie(IStringView key) const;
    ICookiePart getRequestCookie(const QString& key) const;
    QList<ICookiePart> getRequestCookies(IStringView key) const;
    QList<ICookiePart> getRequestCookies(const QString& key) const;

    IStringViewList requestCookieKeys() const;

    bool containRequestCookieKey(IStringView key) const;
    bool containRequestCookieKey(const QString& key) const;

    void deleteRequestCookies(IStringView key);
    void deleteRequestCookies(const QString& key);

    // response
    std::list<ICookiePart>& responseCookies();
    const std::list<ICookiePart>& responseCookies() const;
    ICookiePart getResponseCookie(const QString& key) const;
    QStringList responseCookieKeys() const;
    bool containResponseCookieKey(const QString& key) const;
    void deleteResponseCookie(const QString& key);

    template<typename T>        // in latter c++14, you can pass 1h, 24h type.
    void addResponseCookie(QString key, QString value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    void addResponseCookie(ICookiePart cookiePart);
    void addResponseCookie(QString key, QString value);
    void addResponseCookie(QString key, QString value, int maxAge, bool secure=false, bool httpOnly=false);
    void addResponseCookie(QString key, QString value, QDateTime expires, bool secure=false, bool httpOnly=false);
};

template<typename T>
void ICookieJar::addResponseCookie(QString key, QString value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
{
    ICookiePart part(std::move(key), std::move(value), duration, secure, httpOnly);
    addResponseCookie(std::move(part));     // TODO: test whether move works
}

$PackageWebCoreEnd
