#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpRequestTimeoutInvalid : public IHttpInvalidInterface<IHttpRequestTimeoutInvalid>
{
public:
    IHttpRequestTimeoutInvalid(const QString& description="");
};

$PackageWebCoreEnd
