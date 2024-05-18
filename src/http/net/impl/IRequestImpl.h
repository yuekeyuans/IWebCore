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
        Start, FirstLine, Header, HeaderGap, End,
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
        int contentLength;         //Content-Type
        QString multipartBoundary;   //multipart

        bool getLine(int*);     // 读取下一行数据
        void configBoundary(const QString &mime);
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

private:
    void doRead();
    void doWrite();

private:
    // get
    QString getFormUrlValue(const QString &name, bool& ok) const;
    QByteArray getMultiPartFormData(const QString &name, bool& ok) const;
    QByteArray getJsonData(const QString &name, bool& ok) const;
    QList<QPair<QString, FunType>> parameterResolverMap() const;

    void parseData();
    void startState(int[2]);
    void firstLineState(int[2]);
    void headerState(int[2]);
    bool headerGapState();
    void endState();

    void parseFirstLine(QString data);
    void resolveFirstLine();    // 解析里面所得到的信息
    void parseHeader(QString data);
    void resolveHeaders();      // 解析接收到的头
    void resolveCookieHeaders();
    void parseMultiPartBody();
    bool resolveFormedData(const QString& content, bool isBody);
    void parseCommonBody();

public:
    IReqRespRaw* raw;
    asio::ip::tcp::socket m_socket;
    Data m_data;
};


$PackageWebCoreEnd

