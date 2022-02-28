#include <IWebCore>
#include <QtTest>

#include "TestConfig.h"
#include "TestFunctionCallConfiger.h"


$EnableConfigFile("abc.tt");
int main(int argc, char *argv[])
{
    $ITestBegin
    ITaskManage::run(argc, argv);

    $ITestClass(TestConfig);
    $ITestClass(TestFunctionCallConfiger)

    $ITestEnd
}
