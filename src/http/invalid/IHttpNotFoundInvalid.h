#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"
#include "http.h"

$PackageWebCoreBegin

class IHttpNotFoundInvalid : public IHttpInvalidInterface<IHttpNotFoundInvalid>
{
public:
    IHttpNotFoundInvalid();
    IHttpNotFoundInvalid(const std::string& description);
    // TODO: 这个可以直接使用 IStringData, 这样更好！！！
};

$PackageWebCoreEnd
