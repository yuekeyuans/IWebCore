#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
//#include "IInvalidResponse.h"

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
//    IJsonResponse(const QJsonValue&);
//    IJsonResponse(const QJsonArray&);
//    IJsonResponse(const QJsonObject&);

public:
    virtual QString prefixMatcher() final;
};

IJsonResponse operator"" _json(const char* str, size_t size);

$PackageWebCoreEnd
