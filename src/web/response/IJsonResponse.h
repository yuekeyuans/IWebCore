#pragma once

#include <QtCore>
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
//#include "core/base/IConvertUtil.h"
#include "core/base/IJsonUtil.h"

$PackageWebCoreBegin

class IRedirectResponse;

class IJsonResponse : public IResponseInterface<IJsonResponse>
{
    $AsResponse(IJsonResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IJsonResponse();
    IJsonResponse(const QString&);
    IJsonResponse(const QJsonValue&);
    IJsonResponse(const QJsonArray&);
    IJsonResponse(const QJsonObject&);
    template<typename T>
    IJsonResponse(const T&);

    virtual void setInstanceArg(QString &&) final;
//    virtual void setInstanceArg(void *arg, const QString& type) final;
//    virtual void setInstanceArg(QJsonObject obj);
//    virtual void setInstanceArg(QJsonArray array);
//    virtual void setInstanceArg(QJsonValue array);

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
    raw->setContent(IJsonUtil::toString(jsonValue));
}

IJsonResponse operator"" _json(const char* str, size_t size);

$PackageWebCoreEnd
