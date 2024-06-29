#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/jar/IJarUnit.h"

$PackageWebCoreBegin

class IHeaderJar : public IJarUnit, IRegisterMetaTypeUnit<IHeaderJar>
{
public:
    using IJarUnit::IJarUnit;

public:
    IHeaderJar();
    const QMultiHash<IStringView, IStringView>& requestHeaders() const;
    QMultiHash<IStringView, IStringView>& requestHeaders();

    IStringViewList requestHeaderKeys() const;
    bool containRequestHeaderKey(IStringView key) const;
    bool containRequestHeaderKey(const QString& key) const;

    IStringView getRequestHeaderValue(IStringView key) const;
    IStringView getRequestHeaderValue(const QString& key) const;
    IStringViewList getRequestHeaderValues(IStringView key) const;
    IStringViewList getRequestHeaderValues(const QString& key) const;

    const QMultiHash<QString, QString>& responseHeaders() const;
    QMultiHash<QString, QString>& responseHeaders();

    QStringList responseHeaderKeys() const;
    bool containResponseHeaderKey(const QString& key) const;

    void addResponseHeader(QString key, QString value);
    void addResponseHeader(QString key, const QStringList& values);
    void setResponseHeader(QString key, QString value);
    void setResponseHeader(QString key, const QStringList& values);
    void deleteReponseHeader(const QString& key);
};

$PackageWebCoreEnd
