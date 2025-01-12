#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IHtmlResponse : public IResponseInterface<IHtmlResponse>
{
    $AsResponse(IHtmlResponse)
public:
    using IResponseInterface::IResponseInterface;
//    using IResponseInterface::operator [];

public:
    IHtmlResponse();
    IHtmlResponse(const QString& data);
    IHtmlResponse(std::string&&);
    IHtmlResponse(const std::string&);
    IHtmlResponse(QByteArray&&);
    IHtmlResponse(const QByteArray&);

public:
    virtual std::string prefixMatcher() final;
};

IHtmlResponse operator"" _html(const char* str, size_t size);

$PackageWebCoreEnd
