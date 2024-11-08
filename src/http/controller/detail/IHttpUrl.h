#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/detail/IHttpUrlFragment.h"

$PackageWebCoreBegin

struct IHttpUrl
{
public:
    QString url;
    std::vector<IHttpUrlFragment> fragments;
};

$PackageWebCoreEnd
