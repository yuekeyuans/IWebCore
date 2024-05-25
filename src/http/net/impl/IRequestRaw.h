#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/result/IResult.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/jar/IMultiPart.h"
#include "http/jar/ICookiePart.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;
class IHeaderJar;
class ICookieJar;
class ISessionJar;
class IMultiPartJar;
class IRequestRaw
{
public:
    IRequestRaw();
    IRequestRaw(IRequest* request);
    ~IRequestRaw();

public:
    bool valid() const;
    void setInvalid(IHttpInvalidUnit ware);

    QJsonValue getRequestJson(bool& ok);
    IResult<QJsonValue> getRequestJson();
//    QDomNode&   getRequestXml(bool& ok);

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
    IResponseRaw* m_responseRaw{nullptr};
    IResponse*  m_response {nullptr};
    IRequest*   m_request  {nullptr};
    QMap<QString, QVariant> m_attribute;                // 用户或系统可以自己放置内容的地方。

    // request
    QString m_realUrl;                                  // TODO: 考虑优化掉
    QString m_url;
    IHttpVersion m_httpVersion {IHttpVersion::UNKNOWN};
    IHttpMethod m_method {IHttpMethod::UNKNOWN};
    IHttpMime m_requestMime {IHttpMime::UNKNOWN};
    QByteArray m_requestBody;

    QMultiHash<QString, QString> m_requestHeaders;
    QMap<QString, QString> m_requestUrlParameters;
    QMap<QString, QString> m_requestPathParameters;     // 特指 url 参数后面的内容
    QMap<QString, QString> m_requestBodyParameters;  // 特指 url encoded
    QVector<IMultiPart> m_requestMultiParts;
    QMultiHash<QString, QString> m_requestCookieParameters;

    IHeaderJar* m_headerJar{nullptr};
    ICookieJar* m_cookieJar{nullptr};                                       // TODO: 这两个是否需要指针?
    IMultiPartJar* m_multiPartJar{nullptr};
    ISessionJar* m_sessionJar{nullptr};

private:    
    bool isJsonInited   {false};
    bool isXmlInited    {false};
    QJsonValue m_requestJson;                   // json 和 dom 不一定使用，也可能是延后加载
    QDomNode m_requestXml;
};

$PackageWebCoreEnd
