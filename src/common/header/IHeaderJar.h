#pragma once

#include "base/IHeaderUtil.h"
#include "common/support/IJarUnit.h"
#include "common/support/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

class IReqRespRaw;

class IHeaderJar : IRegisterMetaTypeUnit<IHeaderJar>, public IJarUnit
{
    Q_GADGET
    $UseMetaRegistration(IHeaderJar)
public:
    IHeaderJar() = default;

    // request
    QStringList requestHeaderKeys();
    QString getRequestHeaderValue(const QString& key, bool* ok) const;
    const QMap<QString, QByteArray> requestHeaders() const;



    virtual bool isValid() const final;

private:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};


$PackageWebCoreEnd
