#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IResponseHeader.h"
#include "IResponseContent.h"

$PackageWebCoreBegin

class IRedirectResponse;

class IResponseWare
{
public:
    IResponseWare();
    IResponseWare(const IResponseWare&);
    virtual ~IResponseWare();

    IResponseWare(IResponseWare&&);
    IResponseWare& operator =(const IResponseWare&);
    IResponseWare& operator =(IResponseWare&&);
    IResponseHeader operator[](const QString& header);

public:
    const QString& mime() const;
    void setMime(IHttpMime);
    
    IHttpStatus status() const;
    void setStatus(IHttpStatus statusCode);

    const QMultiHash<QString, QString>& headers() const;
    QMultiHash<QString, QString>& headers();
    void setHeader(const QString& key, const QString& value);
    void addHeader(const QString& key, const QString& value);

    IResponseContent& getContent();

    virtual QString getPrefixMatcher();

    virtual QSharedPointer<IResponseWare> create(IResponseWare*) = 0;
    virtual QSharedPointer<IResponseWare> create(QString) = 0;

public:
    IResponseRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
