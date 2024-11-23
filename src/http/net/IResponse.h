#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "http/net/impl/IResponseHeader.h"
#include "http/response/IResponsePreProcessor.h"

$PackageWebCoreBegin

class IRequest;
class IResponseWare;
class IRequestImpl;
class IRequestRaw;
class ICookiePart;

class IResponse : IRegisterMetaTypeUnit<IResponse>
{
public:
    IResponse();
    explicit IResponse(IRequest& request);
    ~IResponse();

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

//    IResponse& setContent(const QString& content);
//    IResponse& setContent(const QByteArray& content);
//    IResponse& setContent(QByteArray&& content);
//    IResponse& setContent(const char* content);
    IResponse& setContent(IResponseWare& response);
    IResponse& setContent(IResponseWare&& response);
    IResponse& setContent(IHttpInvalidWare unit);

    IHttpVersion version() const;
    const QString& mime() const;
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
