#pragma once

#include "IJson.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

class IInvalidResponse : public IResponseInterface<IInvalidResponse>
{
    $AsResponse(IInvalidResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IInvalidResponse() = default;
    IInvalidResponse(const QString&){}
    IInvalidResponse(IHttpInvalidWare ware);
};

$PackageWebCoreEnd
