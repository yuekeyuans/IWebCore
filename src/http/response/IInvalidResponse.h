#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "http/invalid/IHttpInvalidUnit.h"

$PackageWebCoreBegin

class IInvalidResponse : public IResponseInterface<IInvalidResponse>
{
    $AsResponse(IInvalidResponse)
public:
    using IResponseInterface::IResponseInterface;

public:
    IInvalidResponse() = default;
    IInvalidResponse(const QString& value);
    IInvalidResponse(IHttpInvalidUnit ware);
};

$PackageWebCoreEnd
