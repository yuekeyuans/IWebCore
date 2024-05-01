#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/result/IResult.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/net/impl/IResponseRaw.h"
#include "IResponseContent.h"
#include "http/response/IResponseHeaderRef.h"

$PackageWebCoreBegin

class IRedirectResponse;

class IResponseWare
{
public:
    IResponseWare();
    virtual ~IResponseWare();
    IResponseWare(const IResponseWare&);
    IResponseWare(IResponseWare&&);
    IResponseWare& operator =(const IResponseWare&);
    IResponseWare& operator =(IResponseWare&&);
    IResponseHeaderRef operator[](const QString& header);

public:
    const QString& mime() const;
    void setMime(IHttpMime);
    
    IHttpStatusCode status() const;
    void setStatus(IHttpStatusCode statusCode);

    const QMultiHash<QString, QString>& headers() const;
    void setHeader(const QString& key, const QString& value);

    IResponseContent& getContent();

    virtual QString getPrefixMatcher();

    virtual QSharedPointer<IResponseWare> create(IResponseWare*) = 0;
    virtual QSharedPointer<IResponseWare> create(QString) = 0;

public:
    IResponseRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
