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
public:
    IStringView m_rawUrl;
    IStringView m_rawPath;
    IStringView m_rawPathArgs;
    IStringView m_url;

    IHttpVersion m_httpVersion {IHttpVersion::UNKNOWN};
    IHttpMethod m_method {IHttpMethod::UNKNOWN};
    IHttpMime m_requestMime {IHttpMime::UNKNOWN};
    IStringView m_requestBody;

    QMultiHash<IStringView, IStringView> m_requestHeaders;
    QMap<IStringView, IStringView> m_requestUrlParameters;
    QMap<IStringView, IStringView> m_requestPathParameters;     // 特指 url 参数后面的内容
    QMap<IStringView, IStringView> m_requestBodyParameters;  // 特指 url encoded
    QVector<IMultiPart> m_requestMultiParts;
    QMultiHash<IStringView, IStringView> m_requestCookieParameters;

    IJson m_requestJson;
};

$PackageWebCoreEnd
