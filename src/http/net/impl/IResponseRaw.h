#pragma once

#include "core/base/IStringViewStash.h"
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/net/ICookiePart.h"
#include "http/response/content/IResponseContentWare.h"

$PackageWebCoreBegin

class IRequestImpl;
class IResponseWare;
class IHttpInvalidWare;
class IResponseRaw : public IStringViewStash
{
    friend class IRequestImpl;
public:
    IResponseRaw() = default;
    ~IResponseRaw();

public:
    void setHeader(IString key, IString value);

    void setMime(IHttpMime m_mime);
    void setMime(IString&&);

    void setContent(IJson&& data);
    void setContent(const IJson& data);

    void setContent(IString&&);
    void setContent(const IString&);

    void setContent(const QFileInfo& data);
    void setContent(const IHttpInvalidWare& ware);
    void setContent(IResponseContentWare*);

private:
    void setResponseWare(IResponseWare&&);
    void setResponseWare(IResponseWare&);

public:
    std::vector<asio::const_buffer> getContent(IRequestImpl&);

public:
    bool m_isValid{true};
    IString m_mime;
    IHttpStatus m_status {IHttpStatus::OK_200};
    IHttpHeader m_headers;
    std::list<ICookiePart> m_cookies;
    std::list<IResponseContentWare*> m_contents;
};

$PackageWebCoreEnd
