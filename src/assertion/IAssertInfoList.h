#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IAssertInfoList{
    $UseInstance(IAssertInfoList)
private:
    IAssertInfoList();

public:
    static void init();
};

$PackageWebCoreEnd
