#pragma once

#include "core/base/IJsonUtil.h"
#include "core/base/IXmlUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/result/IResult.h"
#include "web/biscuits/IHttpHeader.h"
#include "web/biscuits/IHttpVersion.h"
#include "web/biscuits/IHttpMime.h"
#include "web/biscuits/IHttpStatus.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/jar/IMultiPart.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;
class IReqRespRaw;

class IRequestImpl
{
public:
    using FunType = QByteArray (IRequestImpl::*)(const QString& name, bool& ok) const;

public:
    IRequestImpl(IReqRespRaw* raw);

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
    QByteArray getAppParameter(const QString& name, bool& ok) const;
    QByteArray getSystemParameter(const QString& name, bool& ok) const;

    void resolve();

    bool checkParamDuplicatedNameError(const QString &name) const;

private:
    // get
    QByteArray getFormUrlValue(const QString &name, bool& ok) const;
    QByteArray getMultiPartFormData(const QString &name, bool& ok) const;
    QByteArray getJsonData(const QString &name, bool& ok) const;
    QList<QPair<QString, FunType>> parameterResolverMap() const;

    // resolve
    bool resolvePeerInfo();
    bool resolveFirstLine();
    bool resolveHeaders();
    bool resolveCookies();
    bool resolveBody();
    bool resolveBodyContent();  // 解析body 的具体内容
    bool resolveMultipartFormData();
    bool resolveTrailer();
    bool resolveFormUrlEncoded();
    bool resolveEncodeArguments(const QByteArray& content, bool isBody);
    void processMultiPartHeaders(IMultiPart& part, int start, int end);
    void processMultiPartBody(IMultiPart& part, int start, int end);

    QList<QPair<int, int>> getBoundaries();
    QByteArray getBoundaryParam(const QString& mime);

public:
    IReqRespRaw* raw;
};


$PackageWebCoreEnd

