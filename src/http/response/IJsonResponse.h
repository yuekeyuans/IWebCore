#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IJsonResponse : public IResponseInterface<IJsonResponse>
{
    $AsResponse(IJsonResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IJsonResponse();
    IJsonResponse(const QString&);
//    IJsonResponse(const QJsonValue&);
//    IJsonResponse(const QJsonArray&);
//    IJsonResponse(const QJsonObject&);
    template<typename T>
    IJsonResponse(const T&);        // TODO: 这个要解决一下

public:
    virtual QString getPrefixMatcher() final;
};

// TODO: json
template<typename T>
IJsonResponse::IJsonResponse(const T& value)
{
//    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
//    auto jsonValue = IConvertUtil::toJsonValue(value);
//    m_raw->setContent(IJsonUtil::toString(jsonValue));
}

IJsonResponse operator"" _json(const char* str, size_t size);

$PackageWebCoreEnd
