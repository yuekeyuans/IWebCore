#pragma once

#include "base/IHeaderUtil.h"
#include "bean/IGadgetUnit.h"

$PackageWebCoreBegin

class IBeanWare : public IGadgetUnit
{
    $AsWare
public:
    IBeanWare() = default;
    virtual ~IBeanWare() = default;
};

$PackageWebCoreEnd
