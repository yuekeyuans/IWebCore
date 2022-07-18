#pragma once

#include "base/IHeaderUtil.h"
#include "web/biscuits/IHttpHeader.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/biscuits/IHttpMime.h"
#include "web/biscuits/IHttpStatus.h"
#include "web/biscuits/IHttpVersion.h"
#include "web/net/IMultiPart.h"
#include "web/cookie/ICookieJar.h"
#include "web/cookie/ICookiePart.h"
#include "web/header/IHeaderJar.h"
#include "web/response/IResponseContent.h"
#include "web/session/ISessionJar.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;

class IReqRespRaw
{
public:
    IReqRespRaw();

public:
    bool valid() const;
    void setInvalid(IHttpStatus status, const QString& message);
    void setInvalidIf(bool condition, IHttpStatus status, const QString& message);

    QJsonValue& getRequestJson(bool* ok=nullptr);
    QDomNode&   getRequestXml(bool* ok=nullptr);

public:
    QTcpSocket* m_socket {nullptr};
    IResponse*  m_response {nullptr};
    IRequest*   m_request  {nullptr};

    int peerPort{};
    QHostAddress peerAddress;
    QString peerName;

    bool m_valid{true};
    QMap<QString, QVariant> m_attribute;                // 用户或系统可以自己放置内容的地方。

    // request
    QString m_url;
    IHttpVersion m_httpVersion {IHttpVersion::UNKNOWN};
    IHttpMethod m_method {IHttpMethod::UNKNOWN};
    IHttpMime m_requestMime {IHttpMime::UNKNOWN};

    QByteArray m_requestBody;
    QList<QPair<QString, QString>> m_requestHeaders;

    QMap<QString, QByteArray> m_requestUrlParameters;
    QMap<QString, QByteArray> m_requestParamParameters;     // 特指 url 参数后面的内容
    QMap<QString, QByteArray> m_requestBodyParameters;  // 特指 url encoded
    QVector<IMultiPart> m_requestMultiParts;
    QList<QPair<QString, QString>> m_requestCookieParameters;

    IHeaderJar m_headerJar;
    ICookieJar m_cookieJar;                                       // TODO: 这两个是否需要指针?
    ISessionJar m_sessionJar;

private:
    QJsonValue m_requestJson;                   // json 和 dom 不一定使用，也可能是延后加载
    QDomNode m_requestXml;

    bool isJsonInited   {false};
    bool isXmlInited    {false};

public:
    // response
    IHttpStatus m_responseStatus {IHttpStatus::UNKNOWN};

    QString m_responseMime{"UNKNOWN"};

    QList<QPair<QString, QString>> m_responseHeaders;
    QList<ICookiePart> m_responseCookies;

    IResponseContent m_responseContent;
    //    QByteArray m_responseContent;
};

$PackageWebCoreEnd
