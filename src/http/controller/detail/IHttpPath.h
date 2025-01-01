#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/detail/IHttpPathFragment.h"

$PackageWebCoreBegin

struct IHttpPath
{
public:
    QString path;
    std::vector<IHttpPathFragment> fragments;
};

$PackageWebCoreEnd
