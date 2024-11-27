#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "http/net/impl/IResponseHeader.h"

$PackageWebCoreBegin

class IRequest;
class IResponseWare;
class IRequestImpl;
class ICookiePart;
class IResponse : IRegisterMetaTypeUnit<IResponse>
{
public:
    IResponse();
    ~IResponse() = default;

    IResponse(IRequest& request);
    IResponse(const IResponse&);
    IResponse(IResponse &&);
    IResponse& operator=(const IResponse&);
    IResponse &operator=(IResponse &&);

    IResponseHeader operator[](const QString& header) const;
    IResponse& setHeader(const QString &key, const QString &value);

    IResponse& setStatus(IHttpStatus statusCode);
    IResponse& setStatus(int statusCode);

    IResponse& setMime(IHttpMime mime);
    IResponse& setMime(const QString mime);

    IResponse& addCookie(ICookiePart cookiePart);

    IResponse& setContent(std::string&&);
    IResponse& setContent(const std::string&);

    IResponse& setContent(IStringView);

    IResponse& setContent(QString&&);
    IResponse& setContent(const QString&);

    IResponse& setContent(QByteArray&&);
    IResponse& setContent(const QByteArray&);
    IResponse& setContent(const char*);

    IResponse& setContent(IResponseWare&);
    IResponse& setContent(IResponseWare&&);

    IResponse& setContent(const IHttpInvalidWare&);
    void setInvalid(const IHttpInvalidWare& ware);

    IHttpVersion version() const;
    const IString& mime() const;
    IHttpStatus status() const;
    const QMultiHash<QString, QString>& headers() const;

    const QMap<QString, QVariant>& attributes() const;
    bool hasAttribute(const QString& name) const;
    void setAttribute(const QString& name, const QVariant& value);
    QVariant getAttribute(const QString& name, const QVariant& defaultValue = {}) const;

private:
    IRequestImpl& m_impl;
};

$PackageWebCoreEnd
