#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "IStatusResponse.h"
#include "IInvalidResponse.h"
#include "IRedirectResponse.h"

$PackageWebCoreBegin

class IJsonResponse : public IResponseInterface<IJsonResponse>
{
    $AsResponse(IJsonResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IJsonResponse();
//    IJsonResponse(const IJson&);  // TODO: 之后可以看一下这个是为什么,很奇怪
    IJsonResponse(std::string);
//    IJsonResponse(const std::string&);
    IJsonResponse(const QString&);
    IJsonResponse(const QJsonValue&);
    IJsonResponse(const QJsonArray&);
    IJsonResponse(const QJsonObject&);

public:
    virtual QString getPrefixMatcher() final;
};

IJsonResponse operator"" _json(const char* str, size_t size);

$PackageWebCoreEnd
