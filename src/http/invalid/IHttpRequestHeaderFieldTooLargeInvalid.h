#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpRequestHeaderFieldTooLargeInvalid : public IHttpInvalidInterface<IHttpRequestHeaderFieldTooLargeInvalid>
{
public:
    IHttpRequestHeaderFieldTooLargeInvalid(const std::string& description = "Request Header Field Too Large");
};

$PackageWebCoreEnd
