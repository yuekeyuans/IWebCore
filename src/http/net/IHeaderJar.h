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
    std::vector<IStringView> requestHeaderKeys() const;
    bool containRequestHeaderKey(const IString& key) const;

    IString getRequestHeaderValue(const IString& key) const;
    const std::vector<IString>& getRequestHeaderValues(const IString& key) const;

    IHttpHeader& responseHeaders();

    std::vector<IStringView> responseHeaderKeys() const;
    bool containResponseHeaderKey(const IString& key) const;


    void addResponseHeader(IString key, IString value);
    void addResponseHeader(IString key, const QStringList& values);
    void setResponseHeader(IString key, IString value);
    void setResponseHeader(IString key, const QStringList& values);
//    void setResponseHeader(IString key, const IString&);
    void deleteReponseHeader(const IString& key);
};

$PackageWebCoreEnd
