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
    IResponseHeader operator[](const QString& header);

public:
    const IString& mime() const;
    void setMime(IHttpMime);
    void setMime(IString&&);
    
    IHttpStatus status() const;
    void setStatus(IHttpStatus statusCode);

    const QMultiHash<QString, QString>& headers() const;
    QMultiHash<QString, QString>& headers();
//    void setHeader(const QString& key, const QString& value);
    void setHeader(const QString& key, IString&& value);
//    void addHeader(const QString& key, const QString& value);

    virtual std::string prefixMatcher();
    virtual IResponseWare* prefixCreate(const std::string&);

public:
    IResponseRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
