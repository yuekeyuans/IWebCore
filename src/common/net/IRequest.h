#pragma once

#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"
#include "base/IMetaUtil.h"
#include "common/biscuits/IHttpMethod.h"
#include "common/biscuits/IHttpVersion.h"
#include "common/biscuits/IHttpStatus.h"
#include "common/biscuits/IHttpMime.h"
#include "common/biscuits/IHttpCharset.h"
#include "common/net/IMultiPart.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

class IResponse;
class ICookieJar;
class ISessionJar;
class IHeaderJar;
class IRequestImpl;
class IReqRespRaw;

class IRequest : private IRegisterMetaTypeUnit<IRequest>
{
    Q_GADGET
    $UseMetaRegistration(IRequest)
public:
    IRequest();
    explicit IRequest(QTcpSocket* m_socket);
    ~IRequest();

    const QString operator[](const QString&headerJar) const;

    IResponse* response() const;
    ICookieJar* cookieJar() const;
    ISessionJar* sessionJar() const;
    IHeaderJar* headerJar() const;
    IReqRespRaw* getRaw() const;

    IHttpVersion version() const;
    IHttpCharset charset() const;   // do not call
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
    const QJsonValue& bodyJson(bool* ok=nullptr) const;
    const QDomNode& bodyXml(bool* ok=nullptr) const;

    QByteArray getParameter(const QString& name, bool* ok=nullptr) const;
    QByteArray getMixedParameter(const QString& name, bool* ok=nullptr) const;
    QByteArray getUrlParameter(const QString& name, bool* ok=nullptr) const;
    QByteArray getParamParameter(const QString& name, bool* ok=nullptr) const ;
    QByteArray getHeaderParameter(const QString& name, bool* ok=nullptr) const;
    QByteArray getBodyParameter(const QString& name, bool* ok=nullptr) const;

    QByteArray getCookieParameter(const QString& name, bool* ok=nullptr) const;
    QByteArray getSessionParameter(const QString& name, bool* ok=nullptr) const;
    QByteArray getAppParameter(const QString& name, bool* ok=nullptr) const;
    QByteArray getSystemParameter(const QString& name, bool* ok=nullptr) const;

    const QMap<QString, QVariant>& attributes() const;;
    bool hasAttribute(const QString& name) const;;
    void setAttribute(const QString& name, const QVariant& value);;
    QVariant getAttribute(const QString& name, bool* ok=nullptr) const;

    bool valid() const;
    void setInvalidIf(bool condition, IHttpStatus status, const QString& message) const;
    void setInvalid(IHttpStatus status, const QString& message) const;

private:
    IRequestImpl* impl{nullptr};
    IReqRespRaw*  raw{nullptr};
};

$PackageWebCoreEnd


