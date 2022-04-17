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

    QStringList keys();
    QStringList values();

    void addCookie(const ICookiePart& cookiePart);
    void addCookie(const QString& key, const QString& value);

    // in latter c++14, you can pass 1h, 24h type.
    template<typename T>
    void addCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    void addCookie(const QString& key, const QString& value, int maxAge, bool secure=false, bool httpOnly=false);
    void addCookie(const QString& key, const QString& value, const QDateTime& expires, bool secure=false, bool httpOnly=false);

private:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};

template<typename T>
void ICookieJar::addCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
{
    ICookiePart part(key, value, duration, secure, httpOnly);
    addCookie(part);
}

$PackageWebCoreEnd
