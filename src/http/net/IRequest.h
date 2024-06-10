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

    IStringView operator[](IStringView header) const;
    IStringView operator[](const QString& header) const;

    IResponse* response() const;
    ICookieJar* cookieJar() const;
    ISessionJar* sessionJar() const;
    IHeaderJar* headerJar() const;
    IMultiPartJar* multiPartJar() const;
    IRequestRaw* getRaw() const;

    IHttpVersion version() const;
    IHttpMime mime() const;
    IStringView url() const;
    IHttpMethod method() const;

    int bodyContentLength() const;
    IStringView bodyContentType() const;
    IStringView bodyContent() const;

    QMultiHash<IStringView, IStringView>& headers();
    const QMultiHash<IStringView, IStringView>& headers() const;
    const QMap<IStringView, IStringView>& urlParameters() const;
    const QMap<IStringView, IStringView>& paramParameters() const;
    const QMap<IStringView, IStringView>& bodyFormParameters() const;
    const QVector<IMultiPart>& bodyMultiParts() const;
    QJsonValue bodyJson(bool& ok) const;
/*

    IStringView getParameter(const QString& name, bool& ok) const;
    IResult<IStringView> getParameter(const QString& name) const;      // 考虑删掉

    IStringView getMixedParameter(const QString& name, bool& ok) const;
    IResult<IStringView> getMixedParameter(const QString& name) const;

    IStringView getUrlParameter(const QString& name, bool& ok) const;
    IResult<IStringView> getUrlParameter(const QString& name) const;

    IStringView getParamParameter(const QString& name, bool& ok) const ;
    IResult<IStringView> getParamParameter(const QString& name) const ;

    IStringView getHeaderParameter(const QString& name, bool& ok) const;
    IResult<IStringView> getHeaderParameter(const QString& name) const;

    IStringView getBodyParameter(const QString& name, bool& ok) const;
    IResult<IStringView> getBodyParameter(const QString& name) const;

    IStringView getCookieParameter(const QString& name, bool& ok) const;
    IResult<IStringView> getCookieParameter(const QString& name) const;

    QByteArray getSessionParameter(const QString& name, bool& ok) const;
    IResult<QByteArray> getSessionParameter(const QString& name) const;
*/

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
    virtual std::vector<asio::const_buffer> getResult() final;

private:
    IRequestImpl* impl{nullptr};
};

#ifdef USE_INLINE
#define __IN_LINE__ inline
#include "IRequest.ipp"
#endif

$PackageWebCoreEnd


