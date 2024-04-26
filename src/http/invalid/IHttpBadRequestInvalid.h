#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpBadRequestInvalid : public IHttpInvalidInterface<IHttpBadRequestInvalid>
{
public:
    IHttpBadRequestInvalid(const QString& description = "");
};

$PackageWebCoreEnd
