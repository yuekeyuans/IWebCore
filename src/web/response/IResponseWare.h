﻿#pragma once

#include "core/base/IHeaderUtil.h"
#include "web/biscuits/IHttpMime.h"
#include "web/biscuits/IHttpStatus.h"
#include "core/result/IResult.h"
#include "IResponseContent.h"

$PackageWebCoreBegin

struct IResponseWareRaw;
class IRedirectResponse;

class IResponseWare
{
public:
    IResponseWare();
    IResponseWare(const IResponseWare&);
    IResponseWare(IResponseWare&&);
    IResponseWare& operator =(const IResponseWare&);
    IResponseWare& operator =(IResponseWare&&);
    virtual ~IResponseWare();

    QString& operator[](const QString& header);

public:
    const QString& mime() const;
    void setMime(IHttpMime);
    
    IHttpStatus status() const;
    void setStatus(IHttpStatus statusCode);

    const QMap<QString, QString>& headers() const;
    void setHeader(const QString& key, const QString& value);

    IResponseContent& getContent();

//    void redirectTo(IRedirectResponse&& redirectResponse);

    virtual void setInvalid(IHttpStatus, QString reason);
    virtual QString getPrefixMatcher();

    virtual QSharedPointer<IResponseWare> create(IResponseWare*) = 0;
    virtual QSharedPointer<IResponseWare> create(QString) = 0;

public:
    IResponseWareRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
