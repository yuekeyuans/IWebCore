#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "web/server/IServerWare.h"

$PackageWebCoreBegin

template<typename T>
class IServerInterface : public  IServerWare, public ISingletonUnit<T>
{
};

$PackageWebCoreEnd
