﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/detail/IResponseRaw.h"


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
//    IResponseHeader operator[](const IString& header);

public:
    const IString& mime() const;
    void setMime(IHttpMime);
    
    IHttpStatus status() const;
    void setStatus(IHttpStatus statusCode);

    const IHttpHeader& headers() const;
    IHttpHeader& headers();

    void setHeader(IStringView key, IStringView value);

    void setCookie(ICookiePart&&);
    void setCookie(const ICookiePart&);
    void setCookie(const IString& key, const IString& value);

    virtual std::string prefixMatcher();
    virtual IResponseWare* prefixCreate(const std::string&);

public:
    IResponseRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
