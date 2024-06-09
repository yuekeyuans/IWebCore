#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
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

    QList<IStringView> requestHeaderKeys() const;
    bool containRequestHeaderKey(IStringView key) const;
    bool containRequestHeaderKey(std::string key) const;
    bool containRequestHeaderKey(const QString& key) const;

    QString getRequestHeaderValue(const QString& key, bool& ok) const;
    IStringView getRequestHeaderValue(IStringView view, bool& ok) const;
//    QStringList getRequestHeaderValues(const QString& key) const;

    const QMultiHash<QString, QString>& responseHeaders() const;
    QMultiHash<QString, QString>& responseHeaders();

    QStringList responseHeaderKeys() const;
    bool containResponseHeaderKey(const QString& key) const;

    void addResponseHeader(const QString& key, const QString& value);
    void addResponseHeader(const QString& key, const QStringList& values);
    void setResponseHeader(const QString& key, const QString& value);
    void setResponseHeader(const QString& key, const QStringList& values);

    void deleteReponseHeader(const QString& key);
};

$PackageWebCoreEnd
