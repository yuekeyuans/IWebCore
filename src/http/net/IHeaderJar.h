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

    IStringView getRequestHeaderValue(const IString& key) const;

    IHttpHeader& responseHeaders();

    std::vector<IStringView> responseHeaderKeys() const;
    bool containResponseHeaderKey(IStringView key) const;
    void addResponseHeader(IString key, IString value);
    void deleteReponseHeader(IStringView key);
};

$PackageWebCoreEnd
