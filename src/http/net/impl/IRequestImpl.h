#pragma once

#include "core/util/IXmlUtil.h"
#include "core/util/IConvertUtil.h"
#include "core/base/IResult.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/net/IMultiPart.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;
class IRequestRaw;
class ITcpConnection;
class IResponseImpl;
struct ITcpConnectionData;

class IRequestImpl : public IStringViewStash
{
public:
    enum State{
        FirstLineState, HeaderState, HeaderGapState, BodyState, EndState,
    };

public:
    using FunType = QByteArray (IRequestImpl::*)(const QString& name, bool& ok) const;

public:
    IRequestImpl(IRequest* self);
    ~IRequestImpl();

//    QJsonValue requestJson(bool& ok) const;
    int contentLength() const;
    IStringView contentType() const;

public:
    void parseData();
    std::vector<asio::const_buffer> getResult();

private:
    void firstLineState(IStringView);
    void headerState(IStringView);
    bool headerGapState();
    void bodyState();
    void endState();

private:
    void parseFirstLine(IStringView);
    void resolveFirstLine();
    void parseHeader(IStringView);
    void resolveHeaders();      // 解析接收到的头
    void resolveCookieHeaders();
    void resolvePathProcessor();
    void resolveBodyContent();
    void resolveMultipartContent();
    void parseUrlEncodedData(IStringView data, bool isBody);
    void parseJsonData(IStringView data);
    void parseMultiPartData(IStringView data);

private:
    IStringView getBoundary(IStringView);

public:
    IRequest* m_request{};
    IRequestRaw* m_raw{};
    ITcpConnection* m_connection{};
    ITcpConnectionData& m_data;
    IResponseImpl* m_responseImpl{};    // TODO: 这个应该可以去掉的。

private:
    State m_readState{FirstLineState};
    bool m_bodyInData{true};    // 表示数据存放在 data 上面
    int m_contentLength{};
    IStringView m_multipartBoundary;
    IStringView m_multipartBoundaryEnd;

private:
    std::list<QByteArray> m_stash;
};

$PackageWebCoreEnd

