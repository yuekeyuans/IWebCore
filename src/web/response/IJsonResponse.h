#pragma once

#include <QtCore>
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
//#include "base/IConvertUtil.h"
#include "base/IJsonUtil.h"

$PackageWebCoreBegin

class IRedirectResponse;

class IJsonResponse : public IResponseInterface<IJsonResponse>
{
    Q_GADGET
    $AsResponse(IJsonResponse)
public:
    using IResponseInterface::operator[];

public:
    IJsonResponse();

    IJsonResponse(const QString&);
    IJsonResponse(const QJsonValue&);
    IJsonResponse(const QJsonArray&);
    IJsonResponse(const QJsonObject&);
    IJsonResponse(IRedirectResponse&& redirectResponse);
    template<typename T>
    IJsonResponse(const T&);

    virtual void setInstanceArg(QString &&) final;
    virtual void setInstanceArg(void *arg, const QString& type) final;
    virtual bool canConvertFromString() final;
    virtual bool matchConvertString(const QString &value) final;

    static QSharedPointer<IJsonResponse> createJsonInstance();
    virtual QSharedPointer<IResponseWare> createInstance() final;

private:
    static const QString prefix;
};

template<typename T>
IJsonResponse::IJsonResponse(const T& value)
{
    raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    auto jsonValue = IConvertUtil::toJsonValue(value);
    raw->content = IJsonUtil::toString(jsonValue).toUtf8();
}

IJsonResponse operator"" _json(const char* str, size_t size);

$PackageWebCoreEnd
