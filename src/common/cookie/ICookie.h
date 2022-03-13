#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "common/support/IRegisterMetaTypeUnit.h"
#include "common/cookie/ICookiePart.h"
#include <chrono>

$PackageWebCoreBegin

class IReqRespRaw;
class ICookie;

class ICookie : IRegisterMetaTypeUnit<ICookie>
{
    Q_GADGET
    $UseMetaRegistration(ICookie)
public:
    ICookie() = default;

    QStringList keys();
    QStringList values();

    void setCookie(const ICookiePart& cookiePart);
    void setCookie(const QString& key, const QString& value);

    // in latter c++14, you can pass 1h, 24h type.
    template<typename T>
    void setCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    void setCookie(const QString& key, const QString& value, int maxAge, bool secure=false, bool httpOnly=false);
    void setCookie(const QString& key, const QString& value, const QDateTime& expires, bool secure=false, bool httpOnly=false);

private:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};

template<typename T>
void ICookie::setCookie(const QString& key, const QString& value, std::chrono::duration<T> duration, bool secure, bool httpOnly){
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    setCookie(key, value, seconds, secure, httpOnly);
}

$PackageWebCoreEnd
