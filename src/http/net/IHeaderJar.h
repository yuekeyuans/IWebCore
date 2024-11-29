#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/net/IJarUnit.h"
#include "http/biscuits/IHttpHeader.h"

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
    bool containRequestHeaderKey(const IString& key) const;
//    bool containRequestHeaderKey(const QString& key) const;

    IString getRequestHeaderValue(const IString& key) const;
//    IString getRequestHeaderValue(const QString& key) const;
    const std::vector<IString>& getRequestHeaderValues(const IString& key) const;
//    const std::vector<IString>& getRequestHeaderValues(const QString& key) const;

//    IHttpHeader& responseHeaders();
    IHttpHeader& responseHeaders();

    std::vector<IString> responseHeaderKeys() const;
    bool containResponseHeaderKey(const IString& key) const;


    void addResponseHeader(IString key, IString value);
    void addResponseHeader(IString key, const QStringList& values);
    void setResponseHeader(IString key, IString value);
    void setResponseHeader(IString key, const QStringList& values);
//    void setResponseHeader(IString key, const IString&);
    void deleteReponseHeader(const IString& key);
};

$PackageWebCoreEnd
