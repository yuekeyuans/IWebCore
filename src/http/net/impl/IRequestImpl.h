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
struct ITcpConnectionData;

class IRequestImpl
{
public:
    enum State{
        Start, FirstLine, Header, HeaderGap, End,
    };

public:
    using FunType = QByteArray (IRequestImpl::*)(const QString& name, bool& ok) const;

public:
    IRequestImpl(IRequest* self);
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
    QString getFormUrlValue(const QString &name, bool& ok) const;
    QByteArray getMultiPartFormData(const QString &name, bool& ok) const;
    QByteArray getJsonData(const QString &name, bool& ok) const;
    QList<QPair<QString, FunType>> parameterResolverMap() const;

public:
    void parseData();
    QByteArray getResult();

private:
    void startState(int[2]);
    void firstLineState(int[2]);
    void headerState(int[2]);
    void headerGapState();
    void endState();

    void parseFirstLine(QString data);
    void resolveFirstLine();    // 解析里面所得到的信息
    void parseHeader(QString data);
    void resolveHeaders();      // 解析接收到的头
    void resolveCookieHeaders();
    void parseMultiPartBody();
    bool resolveFormedData(const QString& content, bool isBody);
    void parseCommonBody();
    QString getBoundary(const QString&);

public:
    IRequest* m_request{};
    IRequestRaw* m_raw{};
    ITcpConnection* m_connection{};
    ITcpConnectionData& m_data;
private:
    State m_readState{Start};
    int m_contentLength{};
    QString m_multipartBoundary;
};


$PackageWebCoreEnd

