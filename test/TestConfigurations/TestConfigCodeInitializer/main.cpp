#include "IWebCore"
#include <QtTest>
#include "TestConfig.h"

int main(int argc, char *argv[])
{
    $ITestBegin

    ITaskManage::run(argc, argv);

    $ITestClass(TestConfig)

    $ITestEnd
}
