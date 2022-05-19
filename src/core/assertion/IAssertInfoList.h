#pragma once

#include "base/IPreProcessorUtil.h"
#include "base/IPackageUtil.h"

$PackageWebCoreBegin

class IAssertInfoList{
    $UseInstance(IAssertInfoList)
private:
    IAssertInfoList();

public:
    static void init();
};

$PackageWebCoreEnd
