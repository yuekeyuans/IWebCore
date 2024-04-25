#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "core/result/IResult.h"
#include "IResponseContent.h"

$PackageWebCoreBegin

struct IResponseWareRaw;
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
    QString& operator[](const QString& header);

public:
    const QString& mime() const;
    void setMime(IHttpMime);
    
    IHttpStatusCode status() const;
    void setStatus(IHttpStatusCode statusCode);

    const QMap<QString, QString>& headers() const;
    void setHeader(const QString& key, const QString& value);

    IResponseContent& getContent();

    virtual void setInvalid(IHttpStatusCode, QString reason);
    virtual QString getPrefixMatcher();

    virtual QSharedPointer<IResponseWare> create(IResponseWare*) = 0;
    virtual QSharedPointer<IResponseWare> create(QString) = 0;

public:
    IResponseWareRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
