#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpUriTooLongInvalid : public IHttpInvalidInterface<IHttpUriTooLongInvalid>
{
public:
    IHttpUriTooLongInvalid();
    IHttpUriTooLongInvalid(const std::string& description);
};

$PackageWebCoreEnd
