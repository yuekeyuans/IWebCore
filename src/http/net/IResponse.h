#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/invalid/IHttpInvalidUnit.h"
#include "http/net/impl/IResponseHeader.h"
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
    IResponseHeader operator[](const QString& header) const;

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
    IResponse& setContent(IHttpInvalidUnit unit);

    IHttpVersion version() const;
    QString mime() const;
    IHttpStatusCode status() const;
    const QMultiHash<QString, QString>& headers() const;

    const QMap<QString, QVariant>& attributes() const;
    bool hasAttribute(const QString& name) const;
    void setAttribute(const QString& name, const QVariant& value);
    QVariant getAttribute(const QString& name, const QVariant& defaultValue = {}) const;
    bool respond();
    bool valid() const;

private:
    IResponseImpl*  m_impl{nullptr};
    IReqRespRaw*    m_raw{nullptr};
};

$PackageWebCoreEnd
