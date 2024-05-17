#pragma once

#include "core/base/IJsonUtil.h"
#include "core/base/IXmlUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/result/IResult.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/jar/IMultiPart.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;
class IReqRespRaw;

class IRequestImpl
{
public:
    enum State{
        Start,
        FirstLine,
        Header,
        HeaderRn,
        Body,
        BodyRn,
        End,
    };

public:
    struct Data{
        char data[1024*8];
        int startPos{};     // 表示当前的起点，前面的数据已经被解析过了。
        int endPos{};       //  当前的终点， 之后的数据还没有传递过来。

        char* extra{};
        int extraLength{};
        int extraPos{};
        int parsedPos{};    // 表示当前parse 到哪个地方了

        State readState{State::Start};    // 当前的 state

        std::array<int, 2> getLine();     // 读取下一行数据

        auto getNextBuffer(){
            return asio::buffer(data + startPos, sizeof(data) - startPos);
        }
    };

public:
    using FunType = QByteArray (IRequestImpl::*)(const QString& name, bool& ok) const;

public:
    IRequestImpl(IRequest* self, asio::ip::tcp::socket socket);
    ~IRequestImpl();

    QJsonValue requestJson(bool& ok) const;

    int contentLength() const;
    QString contentType() const;

    QByteArray getParameter(const QString &name, bool& ok) const;
    QByteArray getMixedParameter(const QString& name, bool& ok) const;
    QByteArray getContentParameter(const QString& name, bool& ok) const;
    QByteArray getUrlParameter(const QString &name, bool& ok) const;
    QByteArray getBodyParameter(const QString &name, bool& ok) const;
    QByteArray getHeaderParameter(const QString &name, bool& ok) const;
    QByteArray getParamParameter(const QString &name, bool& ok) const;
    QByteArray getCookieParameter(const QString &name, bool& ok) const;
    QByteArray getSessionParameter(const QString &name, bool& ok) const;

//    void resolve();
    bool checkParamDuplicatedNameError(const QString &name) const;

private:
    void doRead();


private:
    // get
    QByteArray getFormUrlValue(const QString &name, bool& ok) const;
    QByteArray getMultiPartFormData(const QString &name, bool& ok) const;
    QByteArray getJsonData(const QString &name, bool& ok) const;
    QList<QPair<QString, FunType>> parameterResolverMap() const;

    void parseData();
    void parseFirstLine(QString data);
    void resolveFirstLine();    // 解析里面所得到的信息
    void parseHeader(QString data);
    void resolveHeaders();      // 解析接收到的头

    // resolve
//    bool resolvePeerInfo();
//    bool resolveFirstLine();
//    bool resolveHeaders();
//    bool resolveCookies();
//    bool resolveBody();
//    bool resolveBodyContent();  // 解析body 的具体内容
//    bool resolveMultipartFormData();
//    bool resolveTrailer();
//    bool resolveFormUrlEncoded();
    bool resolveEncodeArguments(const QByteArray& content, bool isBody);
//    void processMultiPartHeaders(IMultiPart& part, int start, int end);
//    void processMultiPartBody(IMultiPart& part, int start, int end);

//    QList<QPair<int, int>> getBoundaries();
//    QByteArray getBoundaryParam(const QString& mime);

public:
    IReqRespRaw* raw;
    asio::ip::tcp::socket m_socket;

private:
    State m_readState{State::Start};
    Data m_data;
};


$PackageWebCoreEnd

