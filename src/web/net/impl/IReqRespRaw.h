#pragma once

#include "base/IHeaderUtil.h"
#include "web/biscuits/IHttpHeader.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/biscuits/IHttpMime.h"
#include "web/biscuits/IHttpStatus.h"
#include "web/biscuits/IHttpVersion.h"
#include "web/net/IMultiPart.h"
#include "web/jar/ICookiePart.h"
#include "web/response/IResponseContent.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;

class IHeaderJar;
class ICookieJar;
class ISessionJar;
class IMultiPartJar;

class IReqRespRaw
{
public:
    IReqRespRaw();
    IReqRespRaw(IRequest* request, QTcpSocket* socket);
    ~IReqRespRaw();

public:
    bool valid() const;
    void setInvalid(IHttpStatus status, const QString& message);
    void setInvalidIf(bool condition, IHttpStatus status, const QString& message);

    QJsonValue& getRequestJson(bool* ok=nullptr);
    QDomNode&   getRequestXml(bool* ok=nullptr);


public:         // 这些东西先抽象出来，等到改变 socket 的时候就相对依赖小一点
    void writeSocket(const QByteArray& content);
    void writeSocket(QByteArray&& content);

    void flushSocket();

    // TODO: 理论上这些函数都应该返回一个状态值， 为了预防端口被关闭的情况, 也为了预防数据发送过慢或者其他出错的情况
    bool waitSocketForReadyRead(int time = 30000);
    QByteArray readSocketLine(qint64 cnt=0);
    QByteArray readSocket(qint64 length);
    bool canSocketReadLine();

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

    IHeaderJar* m_headerJar{nullptr};
    ICookieJar* m_cookieJar{nullptr};                                       // TODO: 这两个是否需要指针?
    IMultiPartJar* m_multiPartJar{nullptr};
    ISessionJar* m_sessionJar{nullptr};

private:
    QJsonValue m_requestJson;                   // json 和 dom 不一定使用，也可能是延后加载
    QDomNode m_requestXml;

    bool isJsonInited   {false};
    bool isXmlInited    {false};

public:
    const IMultiPart m_invalidMultiPart{};      // TODO: 先写在这里，等一下chonggou

public:
    // response
    IHttpStatus m_responseStatus {IHttpStatus::OK_200};

    QString m_responseMime{"UNKNOWN"};

    QList<QPair<QString, QString>> m_responseHeaders;
    QList<ICookiePart> m_responseCookies;

    IResponseContent m_responseContent;
};

$PackageWebCoreEnd
