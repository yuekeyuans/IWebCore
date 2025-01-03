#pragma once

#include "core/base/IStringViewStash.h"
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/net/ICookiePart.h"
#include "http/response/content/IResponseContent.h"

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

    void setContent(const IHttpInvalidWare& ware);
    void setContent(IResponseContent*);

    void setCookie(ICookiePart&&);
    void setCookie(const ICookiePart&);
    void setCookie(const IString& key, const IString& value);

private:
    void setResponseWare(const IResponseWare&);

public:
    std::vector<asio::const_buffer> getContent(IRequestImpl&);

public:
    bool m_isValid{true};
    IString m_mime;
    IHttpStatus m_status {IHttpStatus::OK_200};
    IHttpHeader m_headers;
    std::list<ICookiePart> m_cookies;
    std::list<IResponseContent*> m_contents;
};

$PackageWebCoreEnd
