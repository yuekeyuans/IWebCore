#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IHttpServerManage
{
    $UseInstance(IHttpServerManage)
public:
    IHttpServerManage() = default;

    static void addSocket(qintptr handle);
};

$PackageWebCoreEnd
