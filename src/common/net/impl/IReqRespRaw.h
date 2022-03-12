#pragma once

#include "base/IHeaderUtil.h"
#include "biscuits/IHttpHeader.h"
#include "biscuits/IHttpMethod.h"
#include "biscuits/IHttpMime.h"
#include "biscuits/IHttpStatus.h"
#include "biscuits/IHttpVersion.h"
#include "common/net/IMultiPart.h"
#include "common/cookie/ICookie.h"
#include "common/session/ISession.h"

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
//    qintptr m_socketHandle {};
    QTcpSocket* m_socket{nullptr};
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
    QMap<QString, QByteArray> m_requestHeaders;
    QMap<QString, QByteArray> m_requestUrlParameters;
    QMap<QString, QByteArray> m_requestParamParameters;     // 特指 url 参数后面的内容
    QMap<QString, QByteArray> m_requestBodyParameters;  // 特指 url encoded
    QMap<QString, QString> m_requestCookieParameters;
    QVector<IMultiPart> m_requestMultiParts;
    ICookie m_cookie;                                       // TODO: 这两个是否需要指针?
    ISession m_session;

private:
    QJsonValue m_requestJson;                   // json 和 dom 不一定使用，也可能是延后加载
    QDomNode m_requestXml;

    bool isJsonInited   {false};
    bool isXmlInited    {false};

public:
    // response
    IHttpStatus m_responseStatus {IHttpStatus::UNKNOWN};
    QByteArray m_responseContent;
    IHttpMime m_responseMime{IHttpMime::UNKNOWN};
    QMap<QString, QString> m_responseHeaders;
    QMap<QString, QString> m_responseCookies;
};

$PackageWebCoreEnd
