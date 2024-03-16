#pragma once

#include "core/base/IHeaderUtil.h"
#include "web/biscuits/IHttpMime.h"
#include "web/biscuits/IHttpStatus.h"
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

    virtual void setContent(const QByteArray& bytes);
    virtual void setContent(const QString& content);
    virtual void setContent(const char* content);
    IResponseContent& getContent();

    virtual void parsePrefixCommand(QString &&data);
    virtual void setInstanceCopy(IResponseWare*);

    void redirectTo(IRedirectResponse&& redirectResponse);

    virtual void setInvalid(IHttpStatus, const QString& reason);

    virtual bool canConvertFromString();
    virtual bool matchConvertString(const QString&);

    virtual QSharedPointer<IResponseWare> createInstance();

protected:
    IResponseWareRaw* raw{nullptr};
};

$PackageWebCoreEnd
