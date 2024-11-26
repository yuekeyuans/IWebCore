#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpRequestTimeoutInvalid : public IHttpInvalidInterface<IHttpRequestTimeoutInvalid>
{
public:
    IHttpRequestTimeoutInvalid();
    IHttpRequestTimeoutInvalid(const std::string& description);
};

$PackageWebCoreEnd
