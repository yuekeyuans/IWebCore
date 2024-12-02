#pragma once

#include "core/util/IConvertUtil.h"
#include "core/base/IResult.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/biscuits/IHttpAttribute.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/IMultiPart.h"
#include "http/net/IHeaderJar.h"
#include "http/net/IMultiPartJar.h"
#include "http/net/ICookieJar.h"
#include "http/net/ISessionJar.h"
#include "http/response/content/IResponseContentWare.h"

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
        FirstLineState, HeaderState, HeaderGapState, BodyState, EndState,
    };

public:
    using FunType = QByteArray (IRequestImpl::*)(const QString& name, bool& ok) const;

public:
    IRequestImpl(IRequest& self);
    ~IRequestImpl();


private:
    void parseData();
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
    void resolveBodyContent();
    void resolveMultipartContent();
    void parseUrlEncodedData(IStringView data, bool isBody);
    void parseJsonData(IStringView data);
    void parseMultiPartData(IStringView data);

private:
    IStringView getBoundary(IStringView);

public:
    void setInvalid(const IHttpInvalidWare&);
    void setResponseWare(IResponseWare&& ware);     // used for filter data
    void setResponseWare(IResponseWare& ware);

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

private:
    State m_readState{FirstLineState};
    bool m_bodyInData{true};    // 表示数据存放在 data 上面
    int m_contentLength{};
    IStringView m_multipartBoundary;
    IStringView m_multipartBoundaryEnd;
};

$PackageWebCoreEnd

