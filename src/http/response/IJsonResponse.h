#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "core/base/IJsonUtil.h"

$PackageWebCoreBegin

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
    IJsonResponse(const T&);        // TODO: 这个要解决一下

public:
    virtual QString getPrefixMatcher() final;
};

template<typename T>
IJsonResponse::IJsonResponse(const T& value)
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    auto jsonValue = IConvertUtil::toJsonValue(value);
    m_raw->setContent(IJsonUtil::toString(jsonValue));
}

IJsonResponse operator"" _json(const char* str, size_t size);

$PackageWebCoreEnd
