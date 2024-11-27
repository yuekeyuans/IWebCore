#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/net/IJarUnit.h"

$PackageWebCoreBegin

class IHeaderJar : public IJarUnit, IRegisterMetaTypeUnit<IHeaderJar>
{
public:
    using IJarUnit::IJarUnit;

public:
    IHeaderJar();
//    const QMultiHash<IStringView, IStringView>& requestHeaders() const;
//    QMultiHash<IStringView, IStringView>& requestHeaders();

    std::vector<IString> requestHeaderKeys() const;
    bool containRequestHeaderKey(IStringView key) const;
    bool containRequestHeaderKey(const QString& key) const;

    IString getRequestHeaderValue(IStringView key) const;
    IString getRequestHeaderValue(const QString& key) const;
    const std::vector<IString>& getRequestHeaderValues(IStringView key) const;
    const std::vector<IString>& getRequestHeaderValues(const QString& key) const;

    const QMultiHash<QString, QString>& responseHeaders() const;
    QMultiHash<QString, QString>& responseHeaders();

    QStringList responseHeaderKeys() const;
    bool containResponseHeaderKey(const QString& key) const;


    void addResponseHeader(QString key, QString value);
    void addResponseHeader(QString key, const QStringList& values);
    void setResponseHeader(QString key, QString value);
    void setResponseHeader(QString key, const QStringList& values);
    void setResponseHeader(QString key, const IString&);
    void deleteReponseHeader(const QString& key);
};

$PackageWebCoreEnd
