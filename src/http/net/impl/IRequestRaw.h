#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IResult.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/net/IMultiPart.h"

$PackageWebCoreBegin

class IRequestRaw
{
    friend class IRequestImpl;
private:
    IStringView m_rawUrl;
    IStringView m_rawPath;
    IStringView m_rawPathArgs;

public:
    std::size_t m_contentLength{};
    bool m_isChunked{false};

public:
    IString m_url;
    IString m_body;
    IHttpVersion m_httpVersion {IHttpVersion::UNKNOWN};
    IHttpMethod m_method {IHttpMethod::UNKNOWN};
    IHttpMime m_mime {IHttpMime::UNKNOWN};

    QMap<IStringView, IStringView> m_paths;
    QMap<IString, IString> m_headers;
    QMap<IStringView, IStringView> m_queries;
    QMap<IStringView, IStringView> m_forms;
    std::vector<IMultiPart> m_multiParts;
    QMultiHash<IString, IString> m_cookies;     // 这个可以再封装一下
    IJson m_json;
};

$PackageWebCoreEnd
