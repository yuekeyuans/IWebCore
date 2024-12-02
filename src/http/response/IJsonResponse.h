#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "core/util/IJsonUtil.h"
#include "http/response/content/IStringResponseContent.h"

$PackageWebCoreBegin

class IJsonResponse : public IResponseInterface<IJsonResponse>
{
    $AsResponse(IJsonResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IJsonResponse();
    IJsonResponse(IJson&&);
    IJsonResponse(const IJson&);
    IJsonResponse(const char*);
    IJsonResponse(std::string&&);
    IJsonResponse(const std::string&);
    IJsonResponse(const QString&);

    template<typename T>
    IJsonResponse(T value);

public:
    virtual std::string prefixMatcher() final;
};

IJsonResponse operator"" _json(const char* str, size_t size);

template<typename T>
IJsonResponse::IJsonResponse(T value)
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(new IStringResponseContent(IJsonUtil::toJson(value).dump()));
}

$PackageWebCoreEnd
