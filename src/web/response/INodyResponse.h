#pragma once

#include "core/base/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "IRedirectResponse.h"

$PackageWebCoreBegin

class INodyResponse : public IResponseInterface<INodyResponse>
{
    $AsResponse(INodyResponse)
public:
    using IResponseInterface::operator [];
    using IResponseInterface::IResponseInterface;

public:
    INodyResponse() = default;
    INodyResponse(const QString& path, QJsonObject value);
};

$PackageWebCoreEnd
