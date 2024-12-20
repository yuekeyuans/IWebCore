﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpInternalErrorInvalid : public IHttpInvalidInterface<IHttpInternalErrorInvalid>
{
public:
    IHttpInternalErrorInvalid();
    IHttpInternalErrorInvalid(const std::string& description);
};

$PackageWebCoreEnd
