#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "common/support/IRegisterMetaTypeUnit.h"
#include "common/cookie/ICookiePart.h"

$PackageWebCoreBegin

class IReqRespRaw;

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
    void setCookie(const QString& key, const QString& value, int maxAge, bool secure=false, bool httpOnly=false);
    void setCookie(const QString& key, const QString& value, const QDateTime& expires, bool secure=false, bool httpOnly=false);

private:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};

$PackageWebCoreEnd
