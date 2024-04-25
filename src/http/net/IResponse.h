#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/response/IResponseWareRaw.h"
#include "http/response/IResponsePreProcessor.h"

$PackageWebCoreBegin

class IRequest;
class IResponseWare;
class IRequestImpl;
class IReqRespRaw;
class IResponseImpl;
class ICookiePart;

class IResponse : IRegisterMetaTypeUnit<IResponse>
{
public:
    IResponse();
    explicit IResponse(IRequest* response);
    ~IResponse();

    IResponse(const IResponse&);
    IResponse& operator=(const IResponse&);
    IResponse(IResponse &&);
    IResponse &operator=(IResponse &&);

    IResponse& operator<<(const QString& content);
    IResponse& operator<<(const QByteArray& content);
    IResponse& operator<<(const char* content);
    IResponse& operator<<(IResponseWare* response);
    IResponse& operator<<(IResponseWare& response);
    QString operator[](const QString& header) const;
    QString& operator[](const QString& header);

    IRequest* request() const;
    IReqRespRaw* getRaw() const;

    IResponse& setHeader(const QString &key, const QString &value);
    IResponse& setStatus(IHttpStatusCode statusCode);
    IResponse& setStatus(int statusCode);
    IResponse& setMime(IHttpMime mime);
    IResponse& setMime(const QString mime);
    IResponse& addCookie(const ICookiePart& cookiePart);

    IResponse& appendContent(const QString& content);
    IResponse& appendContent(const QByteArray& content);
    IResponse& appendContent(const char* content);

    IResponse& setContent(const QString& content);
    IResponse& setContent(const QByteArray& content);
    IResponse& setContent(QByteArray&& content);
    IResponse& setContent(const char* content);
    IResponse& setContent(IResponseWare *response);
    IResponse& setContent(IResponseWare& response);

    IHttpVersion version() const;
    QString mime() const;
    IHttpStatusCode status() const;
    const QList<QPair<QString, QString>>& headers() const;

    const QMap<QString, QVariant>& attributes() const;
    bool hasAttribute(const QString& name) const;;
    void setAttribute(const QString& name, const QVariant& value);;
    QVariant getAttribute(const QString& name, const QVariant& defaultValue = {}) const;

    bool respond();

    bool valid() const;
    void setInvalidIf(bool condition, IHttpStatusCode status, const QString& message) const;
    void setInvalid(IHttpStatusCode status, const QString& message) const;

private:
    IResponseImpl*  impl{nullptr};
    IReqRespRaw*    raw{nullptr};
};

$PackageWebCoreEnd
