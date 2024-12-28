#pragma once

#include "core/base/IResult.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/net/IMultiPart.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "http/server/ITcpResolverInterface.h"

$PackageWebCoreBegin

class IResponse;
class ICookieJar;
class ISessionJar;
class IHeaderJar;
class IMultiPartJar;
class ISessionJar;
class IRequestImpl;
class IRequestRaw;
class IHttpAction;
class IRequest :public ITcpResolverInterface
{
    friend class IResponse;
public:
    IRequest() = delete;
    IRequest(const IRequest &) = delete;
    IRequest &operator=(const IRequest &) = delete;
    IRequest(IRequest&&) = delete;
    IRequest& operator=(IRequest&&) = delete;

    explicit IRequest(ITcpConnection&);
    ~IRequest();

public:
    const IString& operator[](const IString& header) const;
    const IString& operator[](const QString& header) const;

public:
    const ICookieJar& cookieJar() const;
    const ISessionJar& sessionJar() const;
    const IHeaderJar& headerJar() const;
    const IMultiPartJar& multiPartJar() const;
    IRequestImpl& impl() const;

public:
    const IString& url() const;
    IHttpVersion version() const;
    IHttpMime mime() const;
    IHttpMethod method() const;

    int contentLength() const;
    const IString& contentType() const;
    const IString& content() const;

    const QMap<IStringView, IStringView>& pathParameters() const;
    const QMap<IStringView, IStringView>& urlParameters() const;
    const QMap<IStringView, IStringView>& paramParameters() const;
    const QMap<IStringView, IStringView>& bodyFormParameters() const;
    const std::vector<IMultiPart>& bodyMultiParts() const;
    const IJson& bodyJson() const;

public:
    IStringView stash(const char* data);
    IStringView stash(QByteArray&& data);
    IStringView stash(const QByteArray& data);
    IStringView stash(const QString& data);
    IStringView stash(std::string&& data);
    IStringView stash(const std::string& data);
    IStringView stash(IString&& data);
    IStringView stash(const IString& data);
    IStringView stash(IStringView data);

public:
    bool isValid() const;
    void setInvalidIf(bool condition, IHttpInvalidWare) const;
    void setInvalid(IHttpInvalidWare) const;

public:
//    void doAction(IHttpAction* action);
    void doWrite();

protected:
    virtual void resolve() final;
    virtual std::vector<asio::const_buffer> getOutput() final;

private:
    IRequestImpl* m_impl{nullptr};
};

$PackageWebCoreEnd


