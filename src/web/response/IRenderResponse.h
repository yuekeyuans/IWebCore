#pragma once

#include "core/base/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "IRedirectResponse.h"

$PackageWebCoreBegin

class IRenderResponse : public IResponseInterface<IRenderResponse>
{
    $AsResponse(IRenderResponse)
public:
    using IResponseInterface::operator [];
    using IResponseInterface::IResponseInterface;

public:
    IRenderResponse() = default;
    IRenderResponse(const QString& path, QJsonObject value);
};

$PackageWebCoreEnd
