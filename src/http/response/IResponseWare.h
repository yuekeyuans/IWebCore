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
    const QString& mime() const;
    void setMime(IHttpMime);
    void setMime(const QString& mime);
    
    IHttpStatus status() const;
    void setStatus(IHttpStatus statusCode);

    const QMultiHash<QString, QString>& headers() const;
    QMultiHash<QString, QString>& headers();
    void setHeader(const QString& key, const QString& value);
    void addHeader(const QString& key, const QString& value);

    virtual QString prefixMatcher();
    virtual IResponseWare* prefixCreate(const QString&);

public:
    IResponseRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
