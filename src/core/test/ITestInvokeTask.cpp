#include "ITestInvokeTask.h"
#include "core/task/ITaskManage.h"
#include "core/test/ITestManage.h"

$PackageWebCoreBegin

QString ITestInvokeTask::name() const
{
    return "Execute All TestCase";
}

QString ITestInvokeTask::catagory() const
{
    return "Test";
}

double ITestInvokeTask::order() const
{
    return 100;
}

void ITestInvokeTask::task()
{
    ITestManage::instance()->invokeAllTestClass();
}

$PackageWebCoreEnd
