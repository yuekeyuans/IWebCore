#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "common/cookie/ICookiePart.h"
#include "common/biscuits/IHttpStatus.h"
#include "common/biscuits/IHttpVersion.h"
#include "common/biscuits/IHttpMime.h"
#include "common/response/IResponseWareRaw.h"
#include "common/response/IResponsePreProcessor.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

class IRequest;
class IResponseWare;
class IRequestImpl;
class IReqRespRaw;
class IResponseImpl;

class IResponse : private IRegisterMetaTypeUnit<IResponse>
{
    Q_GADGET
    $UseMetaRegistration(IResponse)
public:
    IResponse();
    explicit IResponse(IRequest* response);
    ~IResponse() = default;

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
    IResponse& setStatus(IHttpStatus m_statusCode);
    IResponse& setMime(IHttpMime m_responseMime);
    IResponse& addCookie(const ICookiePart& cookiePart);

    IResponse& appendContent(const QString& content);
    IResponse& appendContent(const QByteArray& content);
    IResponse& appendContent(const char* content);

    IResponse& setContent(const QString& content);
    IResponse& setContent(const QByteArray& content);
    IResponse& setContent(QByteArray&& content);
    IResponse& setContent(const char* content);
    IResponse& setContent(IResponseWare *response);

    IHttpVersion version() const;
    IHttpMime mime() const;
    IHttpStatus status() const;
    const QList<QPair<QString, QString>>& headers() const;
    const QByteArray& content() const;

    const QMap<QString, QVariant>& attributes() const;
    bool hasAttribute(const QString& name) const;;
    void setAttribute(const QString& name, const QVariant& value);;
    QVariant getAttribute(const QString& name, const QVariant& defaultValue = {}) const;

    bool respond();

    bool valid() const;
    void setInvalidIf(bool condition, IHttpStatus status, const QString& message) const;
    void setInvalid(IHttpStatus status, const QString& message) const;

private:
    IResponseImpl*  impl{nullptr};
    IReqRespRaw*    raw{nullptr};
};

$PackageWebCoreEnd
