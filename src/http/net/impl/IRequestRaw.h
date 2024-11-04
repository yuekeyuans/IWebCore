#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IResult.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/net/IMultiPart.h"
#include "http/net/ICookiePart.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;
class IHeaderJar;
class ICookieJar;
class ISessionJar;
class IMultiPartJar;
class IHttpAction;
class IRequestRaw
{
public:
    IRequestRaw();
    IRequestRaw(IRequest* request);
    ~IRequestRaw();

public:
    bool isValid() const;
    void setInvalid(IHttpInvalidWare ware);

public:
    IResponseRaw* m_responseRaw{nullptr};
    IResponse*  m_response {nullptr};
    IRequest*   m_request  {nullptr};
    QMap<QString, QVariant> m_attribute;                // 用户或系统可以自己放置内容的地方。

    // request
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

    IHeaderJar* m_headerJar{nullptr};
    ICookieJar* m_cookieJar{nullptr};                                       // TODO: 这两个是否需要指针?
    IMultiPartJar* m_multiPartJar{nullptr};
    ISessionJar* m_sessionJar{nullptr};

    IHttpAction* m_action{};   // 最终处理请求的 动作。
    IJson m_requestJson;
//    QJsonValue m_requestJson;                   // json 和 dom 不一定使用，也可能是延后加载
    QDomNode m_requestXml;
};

$PackageWebCoreEnd
