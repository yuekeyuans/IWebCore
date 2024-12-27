#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/net/IJarUnit.h"
#include "http/biscuits/IHttpHeader.h"

$PackageWebCoreBegin

class IHeaderJar : public IJarUnit
{
public:
    using IJarUnit::IJarUnit;

public:
    std::vector<IStringView> requestHeaderKeys() const;
    bool containRequestHeaderKey(const IString& key) const;

    const IString& getRequestHeaderValue(const IString& key) const;

    IHttpHeader& responseHeaders();

    std::vector<IStringView> responseHeaderKeys() const;
    bool containResponseHeaderKey(const IString& key) const;

    void addResponseHeader(IString key, IString value);
    void addResponseHeader(IString key, const QStringList& values);
    void setResponseHeader(IString key, IString value);
    void setResponseHeader(IString key, const QStringList& values);
    void deleteReponseHeader(const IString& key);
};

$PackageWebCoreEnd
