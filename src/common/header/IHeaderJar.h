#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
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
    bool containRequestHeaderKey(const QString& key);
    const QList<QPair<QString, QByteArray>>& requestHeaders() const;


    // response
    bool containResponseHeaderKey(const QString& key);
    QString getResponseHeaderValue(const QString& key, bool* ok);
    void addResponseHeader(const QString& key, const QString& value);

    virtual bool isValid() const final;

private:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};


$PackageWebCoreEnd
