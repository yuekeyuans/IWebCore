#pragma once
#include "core/util/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "core/util/IConvertUtil.h"

$PackageWebCoreBegin

class IPlainTextResponse : public IResponseInterface<IPlainTextResponse>
{
    $AsResponse(IPlainTextResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IPlainTextResponse();
    virtual ~IPlainTextResponse() = default;

    IPlainTextResponse(QString&& value);
    IPlainTextResponse(const QString& value);
    IPlainTextResponse(const std::string& value);
    IPlainTextResponse(const char* value);

public:
    virtual QString prefixMatcher() final;
};

IPlainTextResponse operator"" _text(const char* str, size_t size);

$PackageWebCoreEnd


