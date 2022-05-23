#pragma once

#include "base/IHeaderUtil.h"
#include "core/ast/IAstInterface.h"

$PackageWebCoreBegin

class IBluePrintControllerTask
{
    $UseInstance(IBluePrintControllerTask);
private:
    IBluePrintControllerTask();

    void registerTask();
};

static IBluePrintControllerTask* task = IBluePrintControllerTask::instance();

$PackageWebCoreEnd
