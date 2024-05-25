#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IPreProcessorUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/result/IResult.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpMime.h"
#include "http/jar/IMultiPart.h"
#include "http/invalid/IHttpInvalidUnit.h"
#include "http/net/server/ITcpResolverInterface.h"


$PackageWebCoreBegin

class IResponse;
class ICookieJar;
class ISessionJar;
class IHeaderJar;
class IMultiPartJar;
class ISessionJar;
class IRequestImpl;
class IRequestRaw;

class IRequest : IRegisterMetaTypeUnit<IRequest>, public ITcpResolverInterface
{
public:
    IRequest();
    explicit IRequest(ITcpConnection*);
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
    IRequestRaw* getRaw() const;

    IHttpVersion version() const;
    IHttpMime mime() const;
    const QString& url() const;
    IHttpMethod method() const;

    int bodyContentLength() const;
    QString bodyContentType() const;
    const QByteArray& bodyContent() const;

    QMultiHash<QString, QString>& headers();
    const QMultiHash<QString, QString>& headers() const;
    const QMap<QString, QString>& urlParameters() const;
    const QMap<QString, QString>& paramParameters() const;
    const QMap<QString, QString>& bodyFormParameters() const;
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

    const QMap<QString, QVariant>& attributes() const;
    bool hasAttribute(const QString& name) const;
    void setAttribute(const QString& name, const QVariant& value);
    QVariant getAttribute(const QString& name, bool& ok) const;
    IResult<QVariant> getAttribute(const QString &name) const;

    bool valid() const;
    void setInvalidIf(bool condition, IHttpInvalidUnit) const;
    void setInvalid(IHttpInvalidUnit) const;

protected:
    virtual void resolve() final;

private:
    IRequestImpl* impl{nullptr};
};

#ifdef USE_INLINE
#define __IN_LINE__ inline
#include "IRequest.ipp"
#endif


$PackageWebCoreEnd


