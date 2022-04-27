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
    QStringList getRequestHeaderValues(const QString& key) const;
    bool containRequestHeaderKey(const QString& key) const;
    const QList<QPair<QString, QByteArray>>& requestHeaders() const;

    // response
    bool containResponseHeaderKey(const QString& key) const;
    QString getResponseHeaderValue(const QString& key, bool* ok) const;
    QStringList getResponseHeaderValues(const QString& key) const;
    void addResponseHeader(const QString& key, const QString& value);

    virtual bool isValid() const final;

private:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};


$PackageWebCoreEnd
