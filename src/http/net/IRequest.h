#pragma once

#include "core/base/IResult.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/net/IMultiPart.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "tcp/ITcpResolver.h"

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
class IRequest : public ITcpResolver
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
    IStringView operator[](const IString& header) const;
    IStringView operator[](const QString& header) const;

public:
    const ICookieJar& cookieJar() const;
    const ISessionJar& sessionJar() const;
    const IHeaderJar& headerJar() const;
    const IMultiPartJar& multiPartJar() const;
    IRequestImpl& impl() const;

public:
    IStringView url() const;
    IHttpVersion version() const;
    IHttpMime mime() const;
    IHttpMethod method() const;

    int contentLength() const;
    IStringView contentType() const;
    IStringView content() const;

    const QMap<IStringView, IStringView>& pathParameters() const;
    const QMap<IStringView, IStringView>& queryParameters() const;
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
    void doWrite();

protected:
    virtual void resolve() final;
    virtual std::vector<asio::const_buffer> getOutput() final;

private:
    IRequestImpl* m_impl{nullptr};
};

$PackageWebCoreEnd


