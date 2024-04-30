#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"
#include "http.h"

$PackageWebCoreBegin

class IHttpNotFoundInvalid : public IHttpInvalidInterface<IHttpNotFoundInvalid>
{
public:
    IHttpNotFoundInvalid(QString description="");
};

$PackageWebCoreEnd
