#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpInternalErrorInvalid : public IHttpInvalidInterface<IHttpInternalErrorInvalid>
{
public:
    IHttpInternalErrorInvalid(const QString& description="");
};

$PackageWebCoreEnd
