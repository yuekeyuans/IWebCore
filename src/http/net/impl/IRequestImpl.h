#pragma once

#include "core/util/IConvertUtil.h"
#include "core/base/IResult.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/biscuits/IHttpAttribute.h"
#include "http/mappings/IHttpAction.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/IMultiPart.h"
#include "http/net/IHeaderJar.h"
#include "http/net/IMultiPartJar.h"
#include "http/net/ICookieJar.h"
#include "http/net/ISessionJar.h"
#include "http/response/content/IResponseContent.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;
class ITcpConnection;
struct ITcpConnectionData;
class IRequestImpl : public IStringViewStash
{
    friend class IRequest;
public:
    enum State{
        FirstLineState, HeaderState, ChunckState, ContentState, EndState
    };

public:
    IRequestImpl(IRequest& self);
    ~IRequestImpl();

private:
    void parseData();
    bool doFirstLineState();
    void firstLineState(std::size_t);
    bool headersState(std::size_t);
    void chunkedState();
    void contentState(std::size_t);
    void endState();

private:
    bool prepareToReadContentLengthData();
    bool prepareToReadChunkedData();

private:
    void parseFirstLine(IStringView);
    void resolveFirstLine();
    void parseHeaders(IStringView);
    void parseHeader(IStringView);
    void parseCookie(IStringView);
    void resolveHeaders();      // 解析接收到的头
    void resolvePayload();
    void parseUrlEncodedData(IStringView data, bool isBody);
    void parseJsonData(IStringView data);
    void parseMultiPartData(IStringView data);
    void parseAction();

private:
    IStringView getBoundary(IStringView);
    void parseChunkedData(IStringView);

public:
    void setInvalid(const IHttpInvalidWare&);
    void setResponseWare(const IResponseWare& ware);

public:
    bool m_isValid{true};
    IRequest& m_request;

public:
    IRequestRaw m_reqRaw{};
    IResponseRaw m_respRaw{};

public:
    IHeaderJar m_headerJar;
    ICookieJar m_cookieJar;                                       // TODO: 这两个是否需要指针?
    IMultiPartJar m_multiPartJar;
    ISessionJar* m_sessionJar{nullptr};
    IHttpAttribute m_attribute;

public:
    ITcpConnection& m_connection;
    ITcpConnectionData& m_data;

public:
    IHttpAction* m_action{};    // 执行当前 http 的 action

private:
    State m_state{FirstLineState};
    bool m_requestComplete{false};
    IStringView m_multipartBoundary;
    IStringView m_multipartBoundaryEnd;
};

$PackageWebCoreEnd
