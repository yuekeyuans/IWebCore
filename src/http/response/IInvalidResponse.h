#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IInvalidResponse : public IResponseInterface<IInvalidResponse>
{
    $AsResponse(IInvalidResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IInvalidResponse() = default;
    IInvalidResponse(const QString& value);
    IInvalidResponse(IHttpInvalidWare ware);
};

$PackageWebCoreEnd
