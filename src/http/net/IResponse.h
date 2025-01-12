#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/invalid/IHttpInvalidWare.h"
//#include "http/net/impl/IResponseHeader.h"

$PackageWebCoreBegin

class IRequest;
class IResponseWare;
class IRequestImpl;
class ICookiePart;
class IResponse
{
public:
    IResponse() = delete;
    IResponse(const IResponse&) = delete;
    IResponse(IResponse &&) = delete;
    IResponse& operator=(const IResponse&) = delete;
    IResponse &operator=(IResponse &&) = delete;
    IResponse(IRequest& request);
    ~IResponse() = default;

public:
//    IResponseHeader operator[](const IString& header) const;
    IResponse& setHeader(IStringView key, IStringView value);

    IResponse& setStatus(IHttpStatus statusCode);
    IResponse& setStatus(int statusCode);

    IResponse& setMime(IHttpMime mime);
    IResponse& setMime(IString mime);

    IResponse& addCookie(ICookiePart cookiePart);

    IResponse& setContent(IString&&);
    IResponse& setContent(const IString&);
    IResponse& setContent(std::string&&);
    IResponse& setContent(const std::string&);
    IResponse& setContent(QByteArray&&);
    IResponse& setContent(const QByteArray&);

    IResponse& setContent(IStringView);
    IResponse& setContent(const QString&);
    IResponse& setContent(const char*);

    IResponse& setContent(const IResponseWare&);    // 对于这个，可以多思考一下，使用引用怎么样
    IResponse& setContent(const IHttpInvalidWare&);

    void setInvalid(const IHttpInvalidWare& ware);

    IHttpVersion version() const;
    const IString& mime() const;
    IHttpStatus status() const;
    const IHttpHeader& headers() const;

private:
    IRequestImpl& m_impl;
};

$PackageWebCoreEnd

