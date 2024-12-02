#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IResponseHeader.h"

$PackageWebCoreBegin

class IRedirectResponse;

class IResponseWare
{
public:
    IResponseWare();
    virtual ~IResponseWare();

    IResponseWare(IResponseWare&&);
    IResponseWare(const IResponseWare &);
    IResponseWare& operator =(const IResponseWare&);
    IResponseWare& operator =(IResponseWare&&);
    IResponseHeader operator[](const IString& header);

public:
    const IString& mime() const;
    void setMime(IHttpMime);
    
    IHttpStatus status() const;
    void setStatus(IHttpStatus statusCode);

    const IHttpHeader& headers() const;
    IHttpHeader& headers();
    // TODO: 这个可以扩展一下，
    void setHeader(IString key, IString value);
    void addHeader(IString key, IString value);

    virtual std::string prefixMatcher();
    virtual IResponseWare* prefixCreate(const std::string&);

public:
    IResponseRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
