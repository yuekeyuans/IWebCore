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
class IRequestRaw;
class ITcpConnection;
class IResponseImpl;
struct ITcpConnectionData;

class IRequestImpl
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

    QJsonValue requestJson(bool& ok) const;
    int contentLength() const;
    IStringView contentType() const;

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
    QString getFormUrlValue(const QString &name, bool& ok) const;
    QByteArray getMultiPartFormData(const QString &name, bool& ok) const;
    QByteArray getJsonData(const QString &name, bool& ok) const;
    QList<QPair<QString, FunType>> parameterResolverMap() const;

public:
    void parseData();
    std::vector<asio::const_buffer> getResult();
    IStringView stash(QByteArray);

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
    void resolveBodyMultipart();
    void resolveFormData(IStringView data, bool isBody);

private:
    IStringView getBoundary(IStringView);
    bool isPathValid(const QString&);

public:
    IRequest* m_request{};
    IRequestRaw* m_raw{};
    ITcpConnection* m_connection{};
    ITcpConnectionData& m_data;
    IResponseImpl* m_responseImpl{};    // TODO: 这个应该可以去掉的。

private:
    State m_readState{FirstLineState};
    int m_contentLength{};
    IStringView m_multipartBoundary;
    IStringView m_multipartBoundaryEnd;
    IStringView m_bodyData{};
    bool m_bodyInData{true};    // 表示数据存放在 data 上面

private:
    std::list<QByteArray> m_stash;
};

$PackageWebCoreEnd

