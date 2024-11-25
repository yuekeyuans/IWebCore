#include "IUnitTestTask.h"
#include "core/test/IUnitTestManage.h"

$PackageWebCoreBegin

void IUnitTestTask::$task()
{
    IUnitTestManage::instance()->invokeTests();
}

$PackageWebCoreEnd
