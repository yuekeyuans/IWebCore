#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "common/support/IRegisterMetaTypeUnit.h"

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

    void setCookie(const QString& key, const QString& value);

private:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};

$PackageWebCoreEnd
