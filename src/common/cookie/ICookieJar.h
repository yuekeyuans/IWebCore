#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "common/support/IRegisterMetaTypeUnit.h"
#include "common/cookie/ICookiePart.h"
#include <chrono>

$PackageWebCoreBegin

class IReqRespRaw;
class ICookieJar;

class ICookieJar : IRegisterMetaTypeUnit<ICookieJar>
{
    Q_GADGET
    $UseMetaRegistration(ICookieJar)
public:
    ICookieJar() = default;

public:
    QStringList requestCookieKeys();
    QStringList requestCookieValues();

    // response 相关

    void deleteRequestCookie(const QString& key);


    void addResponseCookie(const ICookiePart& cookiePart);
    void addResponseCookie(const QString& key, const QString& value);

    // in latter c++14, you can pass 1h, 24h type.
    template<typename T>
    void addResponseCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    void addResponseCookie(const QString& key, const QString& value, int maxAge, bool secure=false, bool httpOnly=false);
    void addResponseCookie(const QString& key, const QString& value, const QDateTime& expires, bool secure=false, bool httpOnly=false);

private:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};

template<typename T>
void ICookieJar::addResponseCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, duration, secure, httpOnly);
    addResponseCookie(part);
}

$PackageWebCoreEnd
