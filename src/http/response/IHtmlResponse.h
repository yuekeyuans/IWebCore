#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IHtmlResponse : public IResponseInterface<IHtmlResponse>
{
    $AsResponse(IHtmlResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IHtmlResponse();
    IHtmlResponse(const char* data);
    IHtmlResponse(const QString& data);

public:
    virtual QString getPrefixMatcher() final;
};

IHtmlResponse operator"" _html(const char* str, size_t size);

$PackageWebCoreEnd
