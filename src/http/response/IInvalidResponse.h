#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

class IInvalidResponse : public IResponseInterface<IInvalidResponse>
{
    $AsResponse(IInvalidResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IInvalidResponse() = default;
    IInvalidResponse(const QString& value);
    IInvalidResponse(IHttpInvalidWare ware);
};

$PackageWebCoreEnd
