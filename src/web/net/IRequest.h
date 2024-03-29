﻿#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IPreProcessorUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/result/IResult.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/biscuits/IHttpVersion.h"
#include "web/biscuits/IHttpStatus.h"
#include "web/biscuits/IHttpMime.h"
#include "web/jar/IMultiPart.h"

$PackageWebCoreBegin

class IResponse;
class ICookieJar;
class ISessionJar;
class IHeaderJar;
class IMultiPartJar;
class ISessionJar;
class IRequestImpl;
class IReqRespRaw;

class IRequest : IRegisterMetaTypeUnit<IRequest>
{
public:
    IRequest();
    explicit IRequest(qintptr handle);
    explicit IRequest(QTcpSocket* m_socket);
    ~IRequest();

    IRequest(const IRequest &);
    IRequest &operator=(const IRequest &);
    IRequest(IRequest&&);
    IRequest& operator=(IRequest&&);

    const QString operator[](const QString& headerJar) const;

    IResponse* response() const;
    ICookieJar* cookieJar() const;
    ISessionJar* sessionJar() const;
    IHeaderJar* headerJar() const;
    IMultiPartJar* multiPartJar() const;
    IReqRespRaw* getRaw() const;

    IHttpVersion version() const;
    IHttpMime mime() const;
    const QString& url() const;
    IHttpMethod method() const;

    int bodyContentLength() const;
    QString bodyContentType() const;
    const QByteArray& bodyContent() const;

    QList<QPair<QString, QString>>& headers();
    const QList<QPair<QString, QString>>& headers() const;
    const QMap<QString, QByteArray>& urlParameters() const;
    const QMap<QString, QByteArray>& paramParameters() const;

    const QMap<QString, QByteArray>& bodyFormParameters() const;
    const QVector<IMultiPart>& bodyMultiParts() const;
    QJsonValue bodyJson(bool& ok) const;
//    const QDomNode& bodyXml(bool& ok) const;

    QByteArray getParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getParameter(const QString& name) const;

    QByteArray getMixedParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getMixedParameter(const QString& name) const;

    QByteArray getUrlParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getUrlParameter(const QString& name) const;

    QByteArray getParamParameter(const QString& name, bool& ok) const ;
    IResult<QByteArray> getParamParameter(const QString& name) const ;

    QByteArray getHeaderParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getHeaderParameter(const QString& name) const;

    QByteArray getBodyParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getBodyParameter(const QString& name) const;


    QByteArray getCookieParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getCookieParameter(const QString& name) const;

    QByteArray getSessionParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getSessionParameter(const QString& name) const;

    QByteArray getAppParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getAppParameter(const QString& name) const;

    QByteArray getSystemParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getSystemParameter(const QString& name) const;

    const QMap<QString, QVariant>& attributes() const;
    bool hasAttribute(const QString& name) const;
    void setAttribute(const QString& name, const QVariant& value);
    QVariant getAttribute(const QString& name, bool& ok) const;
    IResult<QVariant> getAttribute(const QString &name) const;


    bool valid() const;
    void setInvalidIf(bool condition, IHttpStatus status, const QString& message) const;
    void setInvalid(IHttpStatus status, const QString& message) const;

private:
    IRequestImpl* impl{nullptr};
    IReqRespRaw*  raw{nullptr};
};

$PackageWebCoreEnd


