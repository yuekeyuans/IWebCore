#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/unit/IJarUnit.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

class IHeaderJar : public IJarUnit, IRegisterMetaTypeUnit<IHeaderJar>
{
    Q_GADGET
    $UseMetaRegistration(IHeaderJar)
public:
    IHeaderJar() = default;

    // request
    const QList<QPair<QString, QString>>& requestHeaders() const;
    QList<QPair<QString, QString>>& requestHeaders();

    QStringList requestHeaderKeys() const;
    bool containRequestHeaderKey(const QString& key) const;

    QString getRequestHeaderValue(const QString& key, bool* ok) const;
    QStringList getRequestHeaderValues(const QString& key) const;

    // response
    const QList<QPair<QString, QString>>& responseHeaders() const;
    QList<QPair<QString, QString>>& responseHeaders();

    QStringList responseHeaderKeys() const;
    bool containResponseHeaderKey(const QString& key) const;

    QString getResponseHeaderValue(const QString& key, bool* ok) const;
    QStringList getResponseHeaderValues(const QString& key) const;

    void addResponseHeader(const QString& key, const QString& value);
    void setResponseHeader(const QString& key, const QString& value);

    void deleteReponseHeader(const QString& key);

    virtual bool isValid() const final;
};


$PackageWebCoreEnd
