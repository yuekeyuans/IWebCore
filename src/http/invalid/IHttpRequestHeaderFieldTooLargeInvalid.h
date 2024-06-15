#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpRequestHeaderFieldTooLargeInvalid : public IHttpInvalidInterface<IHttpRequestHeaderFieldTooLargeInvalid>
{
public:
    IHttpRequestHeaderFieldTooLargeInvalid(const QString& description = "Request Header Field Too Large");
};

$PackageWebCoreEnd
