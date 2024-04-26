#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IHttpInvalidManage : public ISingletonUnit<IHttpInvalidManage>
{
public:
    IHttpInvalidManage() = default;
};

$PackageWebCoreEnd
